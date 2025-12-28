#ifndef _TITLEBAR_H_
#define _TITLEBAR_H_

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>

class TitleBar : public QWidget
{
	Q_OBJECT

public:
	explicit TitleBar(QWidget* parent);
	~TitleBar();

	// 设置按钮是否可见
	void setButtonVisible(QPushButton* button, bool visible);

	// 设置标题栏的高度
	void setTitleHeight(int height);

protected:
	void paintEvent(QPaintEvent* event) override;

private slots:
	void onClicked();

private:
	QLabel* m_pIconLabel = nullptr;
	QLabel* m_pTitleLabel = nullptr;
	QPushButton* m_pMinimizeButton = nullptr;
	QPushButton* m_pMaximizeButton = nullptr;
	QPushButton* m_pCloseButton = nullptr;

	int m_titleBarHeight = 35;
};


#endif // !_TITLEBAR_H_
