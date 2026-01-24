#include "TestFramelessWindow.h"

TestFramelessWindow::TestFramelessWindow(QWidget* parent) : HWidget(parent)
{
	this->setMinimumSize(800, 600);

	TitleBar* title_bar = new TitleBar(this);
	connect(title_bar, &TitleBar::sendTitleBarButtonEvent, this, &TestFramelessWindow::procTitleBarBtnEvent);
	QVBoxLayout* pLayout = new QVBoxLayout(this);
	pLayout->setMargin(0);
	pLayout->setSpacing(0);
	pLayout->addWidget(title_bar);
	pLayout->addStretch(0);
}

TestFramelessWindow::~TestFramelessWindow()
{
}

void TestFramelessWindow::procTitleBarBtnEvent(TitleBarButtonEvent event)
{
	switch (event)
	{
	case TitleBarButtonEvent::WindowMaximize:
		break;
	case TitleBarButtonEvent::WindowMinimize:
		break;
	case TitleBarButtonEvent::WindowClosed:
		this->close();
		break;
	default:
		break;
	}
}
