#pragma once

#include <QAction>
#include <QLineEdit>
#include <QToolButton>

class MyLineEdit : public QLineEdit
{
public:
	MyLineEdit(QWidget* parent = nullptr);
	~MyLineEdit();

private slots:
	void onPressed();
	void onReleased();

protected:
	void enterEvent(QEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void focusInEvent(QFocusEvent* event) override;
	void focusOutEvent(QFocusEvent* event) override;

private:
	QToolButton* button;
};

