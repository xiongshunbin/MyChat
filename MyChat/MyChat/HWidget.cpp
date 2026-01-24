#include "hwidget.h"

HWidget::HWidget(QWidget *parent)
    :QWidget(parent)
{
    // 绝对不要用 FramelessWindowHint，否则系统不给贴边！
    //Qt默认是自带最大化最小化按钮的，这里再设置一下保险
    setWindowFlags(Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint | Qt::WindowMaximizeButtonHint);

    // 这一步让窗口拥有系统阴影，更现代化和美观
    HWND hwnd = (HWND)this->winId();
    /**
     * 通过 告诉 Windows 虽然我看起来像无边框，但其实我的边框往内容区里延伸了 1 个像素
     * 以此来让 Windows 来给我们画阴影和边框
     */
    const MARGINS shadow = { 1, 1, 1, 1 };
    DwmExtendFrameIntoClientArea(hwnd, &shadow);
}

HWidget::~HWidget()
{

}


bool HWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
#if defined(Q_OS_WIN)
    MSG* msg = static_cast<MSG*>(message);
    HWND hwnd = (HWND)msg->hwnd;

    switch (msg->message) {
    /**
     * ----------核心---------
     * ------隐藏系统边框------
     * 当系统要画边框时，返回 0，告诉它"整个窗口都是我的客户区"
     * 这样系统原本的标题栏和边框就在视觉上消失了
     */
    case WM_NCCALCSIZE: {
        if (msg->wParam == TRUE) {
            // 如果最大化，通常需要微调 resize 区域防止内容被切，这里简化处理直接 return 0 即可满足大部分需求
            *result = 0;
            return true;
        }
        break;
    }

        // 接管鼠标行为
    case WM_NCHITTEST: {
        const int border = 8; // 边缘缩放感应范围
        RECT winRect;
        GetWindowRect(hwnd, &winRect);

        long x = GET_X_LPARAM(msg->lParam);
        long y = GET_Y_LPARAM(msg->lParam);

        // --- 判断边缘缩放 (优先级最高) ---
        bool left = x < winRect.left + border;
        bool right = x >= winRect.right - border;
        bool top = y < winRect.top + border;
        bool bottom = y >= winRect.bottom - border;

        if (top && left) { *result = HTTOPLEFT; return true; }
        if (top && right) { *result = HTTOPRIGHT; return true; }
        if (bottom && left) { *result = HTBOTTOMLEFT; return true; }
        if (bottom && right) { *result = HTBOTTOMRIGHT; return true; }
        if (left) { *result = HTLEFT; return true; }
        if (right) { *result = HTRIGHT; return true; }
        if (top) { *result = HTTOP; return true; }
        if (bottom) { *result = HTBOTTOM; return true; }

        *result = HTCLIENT;//表示点击的是客户区、HTCAPTION 是标题栏，在和标题栏组件联合使用时会遇到
        return true;
    }
    }
#endif
    return QWidget::nativeEvent(eventType, message, result);
}
