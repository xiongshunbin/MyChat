#ifndef HWIDGET_H
#define HWIDGET_H

#include <QWidget>

// 引入 Windows 原生头文件
#if defined(Q_OS_WIN)
#include <windows.h>
#include <windowsx.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#endif

class HWidget : public QWidget
{
    Q_OBJECT

public:
    HWidget(QWidget *parent = nullptr);
    ~HWidget();
protected:
    ///
    /// \brief nativeEvent  拦截Win系统底层消息，类似于mouseEvent就是高层消息
    /// \param eventType    Qt的事件类型标识
    /// \param message      指向操作系统消息的指针，配合操作系统判断
    /// \param result       通过它告诉操作系统这个消息的返回值，例如拖动、缩放或客户区
    /// \return
    ///
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
};

#endif // HWIDGET_H
