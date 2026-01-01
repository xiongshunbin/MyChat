#ifndef _LRDIALOG_H_
#define _LRDIALOG_H_

#include <QWidget>
#include <QMouseEvent>
#include <QStackedWidget>
#include "LoginPanel.h"
#include "RegisterPanel.h"
#include "ForgetPasswordPanel.h"

class LRFDialog : public QWidget
{
	Q_OBJECT
public:
	explicit LRFDialog(QWidget* parent = nullptr);
	~LRFDialog();

	QWidget* initTopBar();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	bool nativeEvent(const QByteArray& eventType, void* message, long* result);

private:
	QPoint pressPos;				// 鼠标点击的位置
	QPoint windowPos;				// 窗口左上角的位置
	bool leftPressed = false;		// 左键是否按下

	QStackedWidget* stackWidget;
	LoginPanel* loginDialog;
	RegisterPanel* registerDialog;
	ForgetPasswordPanel* forgetDialog;
};

#endif // !_LRDIALOG_H_
