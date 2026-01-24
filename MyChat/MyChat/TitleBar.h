#ifndef _TITLEBAR_H_
#define _TITLEBAR_H_

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>

#include "HTitleWidget.h"

enum class TitleBarButtonEvent : uint8_t
{
	WindowMaximize,
	WindowMinimize,
	WindowClosed
};

class TitleBar : public HTitleWidget
{
	Q_OBJECT

public:
	explicit TitleBar(QWidget* parent = nullptr);
	~TitleBar();

	// 设置按钮是否可见
	void setButtonVisible(QPushButton* button, bool visible);

	// 设置标题栏的高度
	void setTitleHeight(int height);

protected:
	void paintEvent(QPaintEvent* event) override;

signals:
	void sendTitleBarButtonEvent(TitleBarButtonEvent event);

private:
	QLabel* m_pIconLabel = nullptr;
	QLabel* m_pTitleLabel = nullptr;
	QPushButton* m_pMinimizeButton = nullptr;
	QPushButton* m_pMaximizeButton = nullptr;
	QPushButton* m_pCloseButton = nullptr;

	int m_titleBarHeight = 35;
};


#endif // !_TITLEBAR_H_
