#ifndef _LOGINPANEL_H_
#define _LOGINPANEL_H_

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "ResourceManager.h"
#include "MyDialog.h"

class LoginPanel : public QWidget
{
	Q_OBJECT
public:
	explicit LoginPanel(QWidget* parent = nullptr);
	~LoginPanel();

protected:
	void initBody();
	void initTail();
	bool eventFilter(QObject* watched, QEvent* event) override;

signals:
	void sendRegister();
	void sendForget();

private:
	void btnEnanle();

private:
	QFont font;
	QPushButton* loginBtn;
	bool userIsNull = true;
	bool passwordIsNull = true;
	bool loginBtnEnabled = false;
};

#endif _LOGINPANEL_H_