#ifndef HTITLEWIDGET_H
#define HTITLEWIDGET_H

#include <QWidget>

class HTitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HTitleWidget(QWidget *parent = nullptr);
    ///
    /// \brief setBackgroundColor   指定背景颜色
    /// \param r                    红
    /// \param g                    绿
    /// \param b                    蓝
    /// \param forceRender          强制渲染，如果上层有样式表，建议启用
    ///
    void setBackgroundColor(const quint8 r,const quint8 g,const quint8 b,bool forceRender = false);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

#endif // HTITLEWIDGET_H
