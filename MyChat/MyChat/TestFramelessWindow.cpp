#include "TestFramelessWindow.h"
#include "Global.h"
#include <QDebug>
#include <QApplication>

TestFramelessWindow::TestFramelessWindow(QWidget* parent) : HWidget(parent)
{
	this->setMinimumSize(800, 600);

	m_titleBar = new TitleBar(this);
	connect(m_titleBar, &TitleBar::sendTitleBarButtonEvent, this, &TestFramelessWindow::procTitleBarBtnEvent);
	QVBoxLayout* pLayout = new QVBoxLayout(this);
	pLayout->setMargin(0);
	pLayout->setSpacing(0);
	pLayout->addWidget(m_titleBar);
	pLayout->addStretch(0);
}

TestFramelessWindow::~TestFramelessWindow()
{
}

void TestFramelessWindow::procTitleBarBtnEvent(TitleBarButtonEvent event)
{
	switch (event)
	{
	case TitleBarButtonEvent::WindowNormalSize:
		this->setWindowState(Qt::WindowNoState);
		break;
	case TitleBarButtonEvent::WindowMaximize:
		this->setWindowState(Qt::WindowMaximized);
		break;
	case TitleBarButtonEvent::WindowMinimize:
		this->setWindowState(Qt::WindowMinimized);
		break;
	case TitleBarButtonEvent::WindowClosed:
		this->close();
		break;
	default:
		break;
	}
}
