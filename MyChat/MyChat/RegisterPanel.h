#pragma once

#include <QWidget>
#include <QFontDatabase>
#include "ResourceManager.h"

class RegisterPanel : public QWidget
{
	Q_OBJECT
public:
	explicit RegisterPanel(QWidget* parent = nullptr);
	~RegisterPanel();

protected:
	void initTitle();
	void initBody();
	void initTail();

signals:
	void sendLogin();

private:
	QFont font;
};