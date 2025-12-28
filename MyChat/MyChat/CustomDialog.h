#ifndef _CUSTOMDIALOG_H_
#define _CUSTOMDIALOG_H_

#include <QWidget>
#include <QPainter>
#include <QEventLoop>
#include <QPropertyAnimation>

class CustomDialog : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(qreal opacity WRITE setOpacity READ opacity)
public:
	enum class ANIMATIONDIRECTION : char
	{
		UPTODOWN,
		DOWNTOUP,
		RIGHTTOLEFT,
		LEFTTORIGHT
	};

public:
	explicit CustomDialog(QWidget* parent = nullptr);
	~CustomDialog();

	void setOpacity(qreal opacity);
	qreal opacity() const;
	void setMainDialog(QWidget* w);
	void showDialog();
	void closeDialog();

	void overlayAnimation();

private slots:
	void slotHideAnimationFinish();

private:
	void startShowAnimation();
	void startHideAnimation();

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	QPropertyAnimation* opacityAnimation = nullptr;
	QPropertyAnimation* showAnimation = nullptr;
	QPropertyAnimation* hideAnimation = nullptr;
	QPropertyAnimation* currentAnimation = opacityAnimation;

	QWidget* mainDialog = nullptr;
	qreal m_opacity = 0;
	QEventLoop m_Loop;
	ANIMATIONDIRECTION m_animationDirection = ANIMATIONDIRECTION::UPTODOWN;
	static const int animationTime = 200;
};

#endif // !_CUSTOMDIALOG_H_

