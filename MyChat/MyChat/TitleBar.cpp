#include "TitleBar.h"
#include "ResourceManager.h"
#include <QEvent>
#include <QMouseEvent>
#include <windows.h>
#include <windowsx.h>

TitleBar::TitleBar(QWidget* parent) : HTitleWidget(parent)
{
	if (parent != nullptr)
	{
		parent->installEventFilter(this);
		connect(this, &TitleBar::sendTitleBarButtonEvent, this, &TitleBar::procTitleBarBtnEvent);
	}
	else
		throw std::runtime_error("The parent widget can't be null!");

	this->setObjectName("TitleBar");
	this->setFixedHeight(m_titleBarHeight);

	m_pIconLabel = new QLabel(this);
	m_pTitleLabel = new QLabel(this);
	m_pMinimizeButton = new QPushButton(this);
	m_pMaximizeButton = new QPushButton(this);
	m_pCloseButton = new QPushButton(this);

	m_pTitleLabel->setObjectName("titleLabel");
	m_pMinimizeButton->setObjectName("minimizeButton");
	m_pMaximizeButton->setObjectName("maximizeButton");
	m_pCloseButton->setObjectName("closeButton");

	m_pIconLabel->setFixedSize(32, 32);
	m_pMinimizeButton->setFixedSize(40, 35);
	m_pMaximizeButton->setFixedSize(40, 35);
	m_pCloseButton->setFixedSize(40, 35);

	QFont iconFont = ResourceManager::getInstance()->getFontPool().find(ResID::Font_TitleBar_iconfont)->second;
	iconFont.setPixelSize(14);

	m_pMinimizeButton->setFont(iconFont);
	m_pMaximizeButton->setFont(iconFont);
	m_pCloseButton->setFont(iconFont);

	m_pMinimizeButton->setText(QChar(0xe650));
	m_pMaximizeButton->setText(QChar(0xe53b));
	m_pCloseButton->setText(QChar(0xe652));

	connect(m_pMinimizeButton, &QPushButton::clicked, this, [&]() {
		emit sendTitleBarButtonEvent(TitleBarEvent::WindowMinimize);
	});
	connect(m_pMaximizeButton, &QPushButton::clicked, this, [&]() {
		windowIsMaximize = !windowIsMaximize;
		TitleBarEvent event;
		if (windowIsMaximize)
		{
			event = TitleBarEvent::WindowMaximize;
		}
		else
		{
			event = TitleBarEvent::WindowNormalSize;
		}
		emit sendTitleBarButtonEvent(event);
	});
	connect(m_pCloseButton, &QPushButton::clicked, this, [&]() {
		emit sendTitleBarButtonEvent(TitleBarEvent::WindowClosed);
	});

	QHBoxLayout* pLayout = new QHBoxLayout(this);
	pLayout->setSpacing(0);
	pLayout->setMargin(0);
	pLayout->addWidget(m_pIconLabel);
	pLayout->addWidget(m_pTitleLabel);
	pLayout->addStretch(0);
	pLayout->addWidget(m_pMinimizeButton);
	pLayout->addWidget(m_pMaximizeButton);
	pLayout->addWidget(m_pCloseButton);

	this->setStyleSheet(ResourceManager::getInstance()->getStylePool().find(ResID::Style_TitleBar)->second);
	this->setContentsMargins(0, 0, 0, 0);
}

TitleBar::~TitleBar()
{
}

void TitleBar::setButtonVisible(QPushButton* button, bool visible)
{
	if (!visible)
		button->hide();
	else
		button->show();
}

void TitleBar::setMargins(int left, int top, int right, int bottom)
{
	this->setContentsMargins(left, top, right, bottom);
}

void TitleBar::setTitleHeight(int height)
{
	if (height < 0)
		height = 0;
	m_titleBarHeight = height;
	setFixedHeight(height);
}

void TitleBar::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event);
	QStyleOption styleOpt;
	styleOpt.init(this);
	QPainter painter(this);
	style()->drawPrimitive(QStyle::PE_Widget, &styleOpt, &painter, this);
}

bool TitleBar::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == parentWidget() && event->type() == QEvent::WindowStateChange)
	{
		if (parentWidget()->isMaximized())
		{
			windowIsMaximize = true;
			m_pMaximizeButton->setText(QChar(0xe53d));
			this->setTitleHeight(44);
			this->setMargins(10, 9, 9, 0);
		}
		else if (parentWidget()->windowState() == Qt::WindowNoState)
		{
			windowIsMaximize = false;
			m_pMaximizeButton->setText(QChar(0xe53b));
			this->setTitleHeight(35);
			this->setMargins(0, 0, 0, 0);
		}
	}
	return QWidget::eventFilter(watched, event);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		//双击最大化/还原
		TitleBarEvent event;
		if (windowIsMaximize)
		{
			event = TitleBarEvent::WindowNormalSize;
		}
		else
		{
			event = TitleBarEvent::WindowMaximize;
		}
		emit sendTitleBarButtonEvent(event);
	}
}

void TitleBar::procTitleBarBtnEvent(TitleBarEvent event)
{
	QWidget* parent = parentWidget();
	if (parent != nullptr)
	{
		switch (event)
		{
		case TitleBarEvent::WindowNormalSize:
			parent->setWindowState(Qt::WindowNoState);
			break;
		case TitleBarEvent::WindowMaximize:
			parent->setWindowState(Qt::WindowMaximized);
			break;
		case TitleBarEvent::WindowMinimize:
			parent->setWindowState(Qt::WindowMinimized);
			break;
		case TitleBarEvent::WindowClosed:
			parent->close();
			break;
		default:
			break;
		}
	}
}
