#include "CustomDialog.h"

CustomDialog::CustomDialog(QWidget* parent) : QWidget(parent)
{
	opacityAnimation = new QPropertyAnimation(this, "opacity", this);
	opacityAnimation->setDuration(animationTime);
	opacityAnimation->setEasingCurve(QEasingCurve::InCirc);
}

CustomDialog::~CustomDialog()
{
}

void CustomDialog::setOpacity(qreal opacity)
{
	m_opacity = opacity;
	update();
}

qreal CustomDialog::opacity() const
{
	return m_opacity;
}

void CustomDialog::setMainDialog(QWidget* w)
{
	mainDialog = w;

	showAnimation = new QPropertyAnimation(mainDialog, "geometry", this);
	showAnimation->setDuration(animationTime);
	showAnimation->setEasingCurve(QEasingCurve::InCirc);

	hideAnimation = new QPropertyAnimation(mainDialog, "geometry", this);
	hideAnimation->setDuration(animationTime);
	hideAnimation->setEasingCurve(QEasingCurve::InCirc);
	connect(hideAnimation, &QPropertyAnimation::finished, this, &CustomDialog::slotHideAnimationFinish);
}

void CustomDialog::showDialog()
{
	currentAnimation = showAnimation;
	show();
	startShowAnimation();
	m_Loop.exec();		// 采用时间循环来实现模态对话框
}

void CustomDialog::closeDialog()
{
	currentAnimation = hideAnimation;
	startHideAnimation();
}

void CustomDialog::startShowAnimation()
{
	overlayAnimation();
	opacityAnimation->setStartValue(0);
	opacityAnimation->setEndValue(0.4);
	opacityAnimation->start();
	if (currentAnimation)
		currentAnimation->start();
}

void CustomDialog::startHideAnimation()
{
	overlayAnimation();
	opacityAnimation->setStartValue(0.4);
	opacityAnimation->setEndValue(0);
	opacityAnimation->start();
	if (hideAnimation)
		hideAnimation->start();
}

void CustomDialog::overlayAnimation()
{
	if (!mainDialog)
		return;

	QRect rect = mainDialog->rect();
	QRect mainRect = this->rect();
	if (currentAnimation == showAnimation)
	{
		switch (m_animationDirection)
		{
		case CustomDialog::ANIMATIONDIRECTION::UPTODOWN:
			showAnimation->setStartValue(QRect((mainRect.width() - rect.width()) / 2,
				0, rect.width(), rect.height()));
			showAnimation->setEndValue(QRect((mainRect.width() - rect.width()) / 2,
				(mainRect.height() - rect.height()) / 2, rect.width(), rect.height()));
			break;
		case CustomDialog::ANIMATIONDIRECTION::DOWNTOUP:
			showAnimation->setStartValue(QRect((mainRect.width() - rect.width()) / 2,
				mainRect.height() - rect.height(), rect.width(), rect.height()));
			showAnimation->setEndValue(QRect((mainRect.width() - rect.width()) / 2,
				(mainRect.height() - rect.height()) / 2, rect.width(), rect.height()));
			break;
		case CustomDialog::ANIMATIONDIRECTION::RIGHTTOLEFT:
			showAnimation->setStartValue(QRect(mainRect.width(),
				(mainRect.height() - rect.height()) / 2, rect.width(), rect.height()));
			showAnimation->setEndValue(QRect((mainRect.width() - rect.width()),
				(mainRect.height() - rect.height()) / 2, rect.width(), rect.height()));
			break;
		case CustomDialog::ANIMATIONDIRECTION::LEFTTORIGHT:
			showAnimation->setStartValue(QRect(-rect.width(),
				(mainRect.height() - rect.height()) / 2, rect.width(), rect.height()));
			showAnimation->setEndValue(QRect(0, (mainRect.height() - rect.height()) / 2, rect.width(), rect.height()));
			break;
		}
	}
	else if (currentAnimation == hideAnimation)
	{
		switch (m_animationDirection)
		{
		case CustomDialog::ANIMATIONDIRECTION::UPTODOWN:
			hideAnimation->setStartValue(QRect((mainRect.width() - rect.width()) / 2,
				(mainRect.height() - rect.height()) / 2, rect.width(), rect.height()));
			hideAnimation->setEndValue(QRect((mainRect.width() - rect.width()) / 2, 0, rect.width(), rect.height()));
			break;
		case CustomDialog::ANIMATIONDIRECTION::DOWNTOUP:
			hideAnimation->setStartValue(QRect((mainRect.width() - rect.width()) / 2,
				(mainRect.height() - rect.height()) / 2, rect.width(), rect.height()));
			hideAnimation->setEndValue(QRect((mainRect.width() - rect.width()) / 2,
				mainRect.height() - rect.height(), rect.width(), rect.height()));
			break;
		case CustomDialog::ANIMATIONDIRECTION::RIGHTTOLEFT:
			hideAnimation->setStartValue(QRect((mainRect.width() - rect.width()),
				(mainRect.height() - rect.height()) / 2, rect.width(), rect.height()));
			hideAnimation->setEndValue(QRect(mainRect.width(), (mainRect.height() - rect.height()) / 2, rect.width(), rect.height()));
			break;
		case CustomDialog::ANIMATIONDIRECTION::LEFTTORIGHT:
			hideAnimation->setStartValue(QRect(0, (mainRect.height() - rect.height()) / 2, rect.width(), rect.height()));
			hideAnimation->setEndValue(QRect(-rect.width(), (mainRect.height() - rect.height()) / 2, rect.width(), rect.height()));
			break;
		}
	}
}

void CustomDialog::slotHideAnimationFinish()
{
	if (m_Loop.isRunning())
		m_Loop.exit();
	this->hide();
}

void CustomDialog::paintEvent(QPaintEvent* event)
{
	Q_UNUSED(event)
		QPainter painter(this);

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::black);
	painter.setBrush(brush);
	painter.setPen(Qt::NoPen);
	painter.setOpacity(m_opacity);        //值越高越不透明
	painter.drawRect(rect());
}
