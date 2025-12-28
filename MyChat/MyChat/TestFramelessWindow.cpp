#include "TestFramelessWindow.h"
#include "TitleBar.h"

TestFramelessWindow::TestFramelessWindow(QWidget* parent)
{
	this->setFixedSize(400, 560);
	TitleBar* title_bar = new TitleBar(this);
	QVBoxLayout* pLayout = new QVBoxLayout(this);
	pLayout->setMargin(0);
	pLayout->setSpacing(0);
	pLayout->addWidget(title_bar);
	pLayout->addStretch(0);
}

TestFramelessWindow::~TestFramelessWindow()
{
}
