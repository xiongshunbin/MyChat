#include <QMouseEvent>
#include <QLabel>
#include <QLineEdit>
#include <QStyleOption>
#include <QPainter>
#include "LoginPanel.h"

LoginPanel::LoginPanel(QWidget* parent) : QWidget(parent)
{
	// ÉèÖÃ¹Ì¶¨´óÐ¡
	this->setFixedSize(400, 524);

	this->setFocusPolicy(Qt::StrongFocus);

	font = ResourcesManager::instance()->getFontPool().find(ResID::Font_PingFang)->second;

	initBody();
	initTail();
}

LoginPanel::~LoginPanel()
{

}

void LoginPanel::initBody()
{
	QWidget* body = new QWidget(this);
	QVBoxLayout* bodyLayout = new QVBoxLayout(body);
	QLabel* logo = new QLabel(this);
	logo->setObjectName("logo");
	logo->setFixedSize(110, 110);
	QPixmap pixLogo(":/src/images/chat.svg");
	logo->setPixmap(pixLogo.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	logo->setAlignment(Qt::AlignCenter);
	logo->move((width() - logo->width()) / 2, (height() - logo->height()) / 8);

	font.setPixelSize(18);
	QLineEdit* editUser = new QLineEdit(body);
	editUser->setFont(font);
	editUser->setClearButtonEnabled(true);
	editUser->setPlaceholderText(u8"ÓÃ»§");
	editUser->setAttribute(Qt::WA_InputMethodEnabled, false);

	QLineEdit* editPassword = new QLineEdit(body);
	editPassword->setFont(font);
	editPassword->setEchoMode(QLineEdit::Password);
	editPassword->setClearButtonEnabled(true);
	editPassword->setPlaceholderText(u8"ÃÜÂë");

	bodyLayout->addWidget(editUser);
	bodyLayout->addWidget(editPassword);

	editUser->setFixedHeight(45);
	editUser->setContextMenuPolicy(Qt::NoContextMenu);
	editPassword->setFixedHeight(45);
	editPassword->setContextMenuPolicy(Qt::NoContextMenu);
	connect(editUser, &QLineEdit::textChanged, this, [=](const QString& str) {
		userIsNull = str.length() == 0;
		btnEnanle();
	});
	connect(editPassword, &QLineEdit::textChanged, this, [=](const QString& str) {
		passwordIsNull = str.length() == 0;
		btnEnanle();
	});

	body->setFixedSize(300, 200);
	body->move((width() - body->width()) / 2, (height() - body->height()) * 1 / 2);

	loginBtn = new QPushButton(this);
	loginBtn->setObjectName("loginBtn");
	loginBtn->setFixedSize(280, 46);
	font.setPixelSize(20);
	loginBtn->setFont(font);
	loginBtn->setText(u8"µÇÂ¼");
	loginBtn->move((width() - loginBtn->width()) / 2, (height() - loginBtn->height()) * 3 / 4);
	loginBtn->installEventFilter(this);
	loginBtn->setEnabled(loginBtnEnabled);

	connect(loginBtn, &QPushButton::clicked, MyDialog::instance(), [&]() {
		MyDialog* dialog = MyDialog::instance();
		dialog->setMessage(u8"µÇÂ¼Ê§°Ü<br/>ÕËºÅ»òÃÜÂë´íÎó£¬ÇëÖØÐÂÊäÈë¡£");
		dialog->exec(window());
	});
}

void LoginPanel::initTail()
{
	QWidget* tail = new QWidget(this);
	tail->setObjectName("tail");
	QHBoxLayout* tailLayout = new QHBoxLayout(tail);
	tail->setFixedSize(200, 50);
	QPushButton* registerBtn = new QPushButton(tail);
	font.setPixelSize(18);
	registerBtn->setFont(font);
	registerBtn->setText(u8"×¢²áÕËºÅ");
	registerBtn->setCursor(Qt::PointingHandCursor);
	connect(registerBtn, &QPushButton::clicked, this, [=]() {
		emit sendRegister();
	});

	QFrame* line = new QFrame(tail);
	line->setFixedHeight(20);
	line->setFrameShape(QFrame::VLine);
	line->setLineWidth(2);

	QPushButton* forgetPasswordBtn = new QPushButton(tail);
	forgetPasswordBtn->setFont(font);
	forgetPasswordBtn->setText(u8"Íü¼ÇÃÜÂë");
	forgetPasswordBtn->setCursor(Qt::PointingHandCursor);
	connect(forgetPasswordBtn, &QPushButton::clicked, this, [=]() {
		emit sendForget();
	});

	tailLayout->addWidget(registerBtn);
	tailLayout->addWidget(line);
	tailLayout->addWidget(forgetPasswordBtn);
	tail->move((width() - tail->width()) / 2, (height() - tail->height()) * 15 / 16);
}

bool LoginPanel::eventFilter(QObject* watched, QEvent* event)
{
	if (watched == loginBtn)
	{
		if (!loginBtnEnabled && event->type() == QEvent::Enter)
			this->setCursor(Qt::ForbiddenCursor);
		else if(event->type() == QEvent::Leave)
			this->setCursor(Qt::ArrowCursor);
	}
	return QWidget::eventFilter(watched, event);
}

void LoginPanel::btnEnanle()
{
	if (!userIsNull && !passwordIsNull)
	{
		loginBtnEnabled = true;
		loginBtn->setCursor(Qt::ArrowCursor);
	}
	else
		loginBtnEnabled = false;
	loginBtn->setEnabled(loginBtnEnabled);
}
