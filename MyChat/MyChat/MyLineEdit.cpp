#include "MyLineEdit.h"

MyLineEdit::MyLineEdit(QWidget* parent) : QLineEdit(parent)
{
	setEchoMode(QLineEdit::Password);
	button->hide();
	connect(button, &QToolButton::pressed, this, &MyLineEdit::onPressed);
	connect(button, &QToolButton::released, this, &MyLineEdit::onReleased);
}

MyLineEdit::~MyLineEdit()
{
}

void MyLineEdit::onPressed()
{

}

void MyLineEdit::onReleased()
{
}

void MyLineEdit::enterEvent(QEvent* event)
{
}

void MyLineEdit::leaveEvent(QEvent* event)
{
}

void MyLineEdit::focusInEvent(QFocusEvent* event)
{
}

void MyLineEdit::focusOutEvent(QFocusEvent* event)
{
}
