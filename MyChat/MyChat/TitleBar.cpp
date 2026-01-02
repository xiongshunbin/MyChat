#include "TitleBar.h"
#include "ResourceManager.h"

TitleBar::TitleBar(QWidget* parent) : QWidget(parent)
{
	this->setObjectName("TitleBar");
	this->setFixedSize(parent->width(), m_titleBarHeight);

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

	QHBoxLayout* pLayout = new QHBoxLayout(this);
	pLayout->setSpacing(0);
	pLayout->setMargin(0);
	pLayout->setAlignment(Qt::AlignVCenter);
	pLayout->addWidget(m_pIconLabel);
	pLayout->addWidget(m_pTitleLabel);
	pLayout->addWidget(m_pMinimizeButton);
	pLayout->addWidget(m_pMaximizeButton);
	pLayout->addWidget(m_pCloseButton);

	this->setStyleSheet(ResourceManager::getInstance()->getStylePool().find(ResID::Style_TitleBar)->second);
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

void TitleBar::onClicked()
{

}
