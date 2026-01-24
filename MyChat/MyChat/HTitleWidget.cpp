#include "htitlewidget.h"
#include <QMouseEvent>
#if defined(Q_OS_WIN)
#include <windows.h>
#endif

HTitleWidget::HTitleWidget(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundColor(247,247,247);
}

void HTitleWidget::setBackgroundColor(const quint8 r, const quint8 g, const quint8 b, bool forceRender)
{
    setAutoFillBackground(true);//启用自动背景绘制
    // 如果上层有样式表，建议同时 setAttribute(Qt::WA_StyledBackground, true)；
    if(forceRender)
    {
        setAttribute(Qt::WA_StyledBackground, true);
    }

    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor( r, g, b));
    setPalette(pal);
}

void HTitleWidget::mouseMoveEvent(QMouseEvent *event)
{
#if defined(Q_OS_WIN)
    if (event->buttons() & Qt::LeftButton) {
        //拖拽
        HWND hwnd = reinterpret_cast<HWND>(this->window()->winId());
        ReleaseCapture();
        SendMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
    }
#else
    QWidget::mouseMoveEvent(event);
#endif
}

void HTitleWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
#if defined(Q_OS_WIN)
    if (event->button() == Qt::LeftButton) {
        //双击最大化/还原
        HWND hwnd = reinterpret_cast<HWND>(this->window()->winId());
#ifdef QT6_OR_LATER
        QPoint globalPos = event->globalPosition().toPoint();
#else
        QPoint globalPos = event->globalPos();
#endif
        LPARAM lParam = MAKELPARAM(globalPos.x(), globalPos.y());
        ReleaseCapture();
        SendMessage(hwnd, WM_NCLBUTTONDBLCLK, HTCAPTION, lParam);
    }
#else
    QWidget::mouseDoubleClickEvent(event);
#endif
}
