#ifndef _TESTFRAMELESSWINDOW_H_
#define _TESTFRAMELESSWINDOW_H_

#include <QWindowStateChangeEvent>
#include "HWidget.h"
#include "TitleBar.h"

class TestFramelessWindow : public HWidget
{
	Q_OBJECT

public:
	explicit TestFramelessWindow(QWidget* parent = nullptr);
	~TestFramelessWindow();

private slots:
	void procTitleBarBtnEvent(TitleBarButtonEvent event);

private:
	TitleBar* m_titleBar;

};

#endif // !_TESTFRAMELESSWINDOW_H_
