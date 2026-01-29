#ifndef _TESTFRAMELESSWINDOW_H_
#define _TESTFRAMELESSWINDOW_H_

#include <QWindowStateChangeEvent>
#include "HWidget.h"
#include "TitleBar.h"

class FramelessWindow : public HWidget
{
	Q_OBJECT

public:
	explicit FramelessWindow(QWidget* parent = nullptr);
	~FramelessWindow();

private:
	TitleBar* m_titleBar;

};

#endif // !_TESTFRAMELESSWINDOW_H_
