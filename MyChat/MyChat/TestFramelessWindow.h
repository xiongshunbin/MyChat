#ifndef _TESTFRAMELESSWINDOW_H_
#define _TESTFRAMELESSWINDOW_H_

#include "FramelessWindow.h"

class TestFramelessWindow : public FramelessWindow
{
	Q_OBJECT

public:
	explicit TestFramelessWindow(QWidget* parent = nullptr);
	~TestFramelessWindow();
};


#endif // !_TESTFRAMELESSWINDOW_H_
