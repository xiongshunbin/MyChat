#pragma once

#include <QWidget>
#include <QFontDatabase>
#include "resources_manager.h"

class ForgetPasswordPanel : public QWidget
{
	Q_OBJECT
public:
	explicit ForgetPasswordPanel(QWidget* parent = nullptr);
	~ForgetPasswordPanel();

protected:
	void initTitle();
	void initBody();
	void initTail();

signals:
	void sendRegister();


private:
	QFont font;
};
