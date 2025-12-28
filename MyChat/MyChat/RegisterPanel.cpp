#include <QStyleOption>
#include <QPainter>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "RegisterPanel.h"

RegisterPanel::RegisterPanel(QWidget* parent) : QWidget(parent)
{
	// ÉèÖÃ¹Ì¶¨´óÐ¡
	this->setFixedSize(400, 524);

	font = ResourcesManager::instance()->getFontPool().find(ResID::Font_PingFang)->second;

	initTitle();
	initBody();
	initTail();
}

RegisterPanel::~RegisterPanel()
{
}

void RegisterPanel::initTitle()
{
	QLabel* regTitleLbl = new QLabel(this);
	regTitleLbl->setFixedSize(200, 50);
	font.setPixelSize(24);
	regTitleLbl->setFont(font);
	regTitleLbl->setText(u8"»¶Ó­×¢²á");
	regTitleLbl->setAlignment(Qt::AlignCenter);
	regTitleLbl->move((width() - regTitleLbl->width()) / 2, (height() - regTitleLbl->height()) / 40);
}

void RegisterPanel::initBody()
{
	QWidget* body = new QWidget(this);
	body->setFixedSize(300, 300);
	QVBoxLayout* bodyLayout = new QVBoxLayout(body);
	font.setPixelSize(18);

	QLineEdit* userEdit = new QLineEdit(body);
	userEdit->setFont(font);
	userEdit->setClearButtonEnabled(true);
	userEdit->setPlaceholderText(u8"ÓÃ»§");

	QLineEdit* passwordEdit = new QLineEdit(body);
	passwordEdit->setFont(font);
	passwordEdit->setEchoMode(QLineEdit::Password);
	passwordEdit->setClearButtonEnabled(true);
	passwordEdit->setPlaceholderText(u8"ÃÜÂë");

	QLineEdit* emailEdit = new QLineEdit(body);
	emailEdit->setFont(font);
	emailEdit->setClearButtonEnabled(true);
	emailEdit->setPlaceholderText(u8"ÓÊÏä");

	QLineEdit* verificationEdit = new QLineEdit(body);
	verificationEdit->setFont(font);
	verificationEdit->setClearButtonEnabled(true);
	verificationEdit->setPlaceholderText(u8"ÑéÖ¤Âë");
	verificationEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]{6}")));
	QPushButton* getBtn = new QPushButton;
	getBtn->setFixedSize(60, 35);
	font.setPixelSize(16);
	getBtn->setFont(font);
	getBtn->setText(u8"»ñÈ¡");
	getBtn->setCheckable(true);
	getBtn->setCursor(Qt::ArrowCursor);
	getBtn->setObjectName("getBtn");
	QHBoxLayout* layout = new QHBoxLayout(verificationEdit);
	layout->setContentsMargins(0, 0, 5, 0);
	layout->addStretch();
	layout->addWidget(getBtn, Qt::AlignCenter);

	bodyLayout->addWidget(userEdit);
	bodyLayout->addWidget(passwordEdit);
	bodyLayout->addWidget(emailEdit);
	bodyLayout->addWidget(verificationEdit);

	userEdit->setFixedHeight(45);
	userEdit->setContextMenuPolicy(Qt::NoContextMenu);
	passwordEdit->setFixedHeight(45);
	passwordEdit->setContextMenuPolicy(Qt::NoContextMenu);
	emailEdit->setFixedHeight(45);
	emailEdit->setContextMenuPolicy(Qt::NoContextMenu);
	verificationEdit->setFixedHeight(45);
	verificationEdit->setContextMenuPolicy(Qt::NoContextMenu);

	body->move((width() - body->width()) / 2, (height() - body->height()) / 4);

	QPushButton* registerBtn = new QPushButton(this);
	registerBtn->setObjectName("registerBtn");
	registerBtn->setFixedSize(280, 46);
	font.setPixelSize(20);
	registerBtn->setFont(font);
	registerBtn->setText(u8"×¢²á");
	registerBtn->move((width() - registerBtn->width()) / 2, (height() - registerBtn->height()) * 4 / 5);
}

void RegisterPanel::initTail()
{
	QWidget* tail = new QWidget(this);
	tail->setObjectName("tail");
	QHBoxLayout* tailLayout = new QHBoxLayout(tail);
	tail->setFixedSize(200, 50);
	QPushButton* loginBtn = new QPushButton(tail);
	loginBtn->setFixedWidth(80);
	font.setPixelSize(18);
	loginBtn->setFont(font);
	loginBtn->setText(u8"ÃÜÂëµÇÂ¼");
	loginBtn->setCursor(Qt::PointingHandCursor);
	connect(loginBtn, &QPushButton::clicked, this, [=]() {
		emit sendLogin();
	});
	tailLayout->addWidget(loginBtn);
	tail->move((width() - tail->width()) / 2, (height() - tail->height()) * 15 / 16);
}