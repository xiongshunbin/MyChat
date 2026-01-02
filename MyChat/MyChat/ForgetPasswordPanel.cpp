#include <QStyleOption>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "ForgetPasswordPanel.h"

ForgetPasswordPanel::ForgetPasswordPanel(QWidget* parent) : QWidget(parent)
{
	// 设置固定大小
	this->setFixedSize(400, 524);

	font = ResourceManager::getInstance()->getFontPool().find(ResID::Font_PingFang)->second;

	initTitle();
	initBody();
	initTail();
}

ForgetPasswordPanel::~ForgetPasswordPanel()
{
}

void ForgetPasswordPanel::initTitle()
{
	QLabel* fgtTitleLbl = new QLabel(this);
	fgtTitleLbl->setFixedSize(200, 50);
	font.setPixelSize(24);
	fgtTitleLbl->setFont(font);
	fgtTitleLbl->setText(u8"修改密码");
	fgtTitleLbl->setAlignment(Qt::AlignCenter);
	fgtTitleLbl->move((width() - fgtTitleLbl->width()) / 2, (height() - fgtTitleLbl->height()) / 40);
}

void ForgetPasswordPanel::initBody()
{
	QWidget* body = new QWidget(this);
	body->setFixedSize(300, 300);
	QVBoxLayout* bodyLayout = new QVBoxLayout(body);
	font.setPixelSize(18);

	QLineEdit* emailEdit = new QLineEdit(body);
	emailEdit->setFont(font);
	emailEdit->setClearButtonEnabled(true);
	emailEdit->setPlaceholderText(u8"邮箱");

	QLineEdit* verificationEdit = new QLineEdit(body);
	verificationEdit->setFont(font);
	verificationEdit->setClearButtonEnabled(true);
	verificationEdit->setPlaceholderText(u8"验证码");
	verificationEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]{6}")));
	QPushButton* getBtn = new QPushButton;
	getBtn->setFixedSize(60, 35);
	font.setPixelSize(16);
	getBtn->setFont(font);
	getBtn->setText(u8"获取");
	getBtn->setCheckable(true);
	getBtn->setCursor(Qt::ArrowCursor);
	getBtn->setObjectName("getBtn");
	QHBoxLayout* layout = new QHBoxLayout(verificationEdit);
	layout->setContentsMargins(0, 0, 5, 0);
	layout->addStretch();
	layout->addWidget(getBtn, Qt::AlignCenter);

	QLineEdit* newPasswordEdit = new QLineEdit(body);
	newPasswordEdit->setFont(font);
	newPasswordEdit->setEchoMode(QLineEdit::Password);
	newPasswordEdit->setClearButtonEnabled(true);
	newPasswordEdit->setPlaceholderText(u8"新密码");

	QLineEdit* confirmPasswordEdit = new QLineEdit(body);
	confirmPasswordEdit->setFont(font);
	confirmPasswordEdit->setEchoMode(QLineEdit::Password);
	confirmPasswordEdit->setClearButtonEnabled(true);
	confirmPasswordEdit->setPlaceholderText(u8"确认密码");

	bodyLayout->addWidget(emailEdit);
	bodyLayout->addWidget(verificationEdit);
	bodyLayout->addWidget(newPasswordEdit);
	bodyLayout->addWidget(confirmPasswordEdit);

	emailEdit->setFixedHeight(45);
	emailEdit->setContextMenuPolicy(Qt::NoContextMenu);
	verificationEdit->setFixedHeight(45);
	verificationEdit->setContextMenuPolicy(Qt::NoContextMenu);
	newPasswordEdit->setFixedHeight(45);
	newPasswordEdit->setContextMenuPolicy(Qt::NoContextMenu);
	confirmPasswordEdit->setFixedHeight(45);
	confirmPasswordEdit->setContextMenuPolicy(Qt::NoContextMenu);

	body->move((width() - body->width()) / 2, (height() - body->height()) / 4);

	QPushButton* confirmBtn = new QPushButton(this);
	confirmBtn->setObjectName("confirmBtn");
	confirmBtn->setFixedSize(280, 46);
	font.setPixelSize(20);
	confirmBtn->setFont(font);
	confirmBtn->setText(u8"确认修改");
	confirmBtn->move((width() - confirmBtn->width()) / 2, (height() - confirmBtn->height()) * 4 / 5);
}

void ForgetPasswordPanel::initTail()
{
	QWidget* tail = new QWidget(this);
	tail->setObjectName("tail");
	QHBoxLayout* tailLayout = new QHBoxLayout(tail);
	tail->setFixedSize(200, 50);
	QPushButton* registerBtn = new QPushButton(tail);
	registerBtn->setFixedWidth(80);
	font.setPixelSize(18);
	registerBtn->setFont(font);
	registerBtn->setText(u8"注册账号");
	registerBtn->setCursor(Qt::PointingHandCursor);
	connect(registerBtn, &QPushButton::clicked, this, [=]() {
		emit sendRegister();
	});
	tailLayout->addWidget(registerBtn);
	tail->move((width() - tail->width()) / 2, (height() - tail->height()) * 15 / 16);
}
