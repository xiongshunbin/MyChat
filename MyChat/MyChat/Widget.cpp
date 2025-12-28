#include "Widget.h"
#include <QIcon>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
	this->setWindowIcon(QIcon(":/MyChat.ico"));
}

Widget::~Widget()
{}
