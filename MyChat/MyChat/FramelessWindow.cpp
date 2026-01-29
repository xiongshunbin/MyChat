#include "FramelessWindow.h"
#include "Global.h"
#include <QDebug>
#include <QApplication>

FramelessWindow::FramelessWindow(QWidget* parent) : HWidget(parent)
{
	this->setMinimumSize(700, 500);

	m_titleBar = new TitleBar(this);
	QVBoxLayout* pLayout = new QVBoxLayout(this);
	pLayout->setMargin(0);
	pLayout->setSpacing(0);

	pLayout->addWidget(m_titleBar);
	pLayout->addStretch(0);
}

FramelessWindow::~FramelessWindow()
{
}
