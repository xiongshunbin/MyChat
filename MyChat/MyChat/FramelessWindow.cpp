#include "FramelessWindow.h"

#ifdef Q_OS_WIN
#include <Dwmapi.h>  // Use system shadow frame
#endif

FramelessWindow::FramelessWindow(QWidget* parent)
{
	// 设置为无边框窗口
	this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

	// 设置窗口阴影效果
#ifdef Q_OS_WIN
	BOOL bEnable = false;
	::DwmIsCompositionEnabled(&bEnable);
	if (bEnable)
	{
		DWMNCRENDERINGPOLICY ncrp = DWMNCRP_ENABLED;
		::DwmSetWindowAttribute((HWND)winId(), DWMWA_NCRENDERING_POLICY, &ncrp, sizeof(ncrp));
		MARGINS margins = { -1 };
		::DwmExtendFrameIntoClientArea((HWND)winId(), &margins);
	}
#endif


}

FramelessWindow::~FramelessWindow()
{
}

bool FramelessWindow::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	return QWidget::nativeEvent(eventType, message, result);
}
