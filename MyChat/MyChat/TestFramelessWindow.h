#ifndef _TESTFRAMELESSWINDOW_H_
#define _TESTFRAMELESSWINDOW_H_

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

};


#endif // !_TESTFRAMELESSWINDOW_H_
