#include <QStyleOption>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegularExpression>
#include "RegisterPanel.h"
#include "ResourceManager.h"
#include "HttpManager.h"

RegisterPanel::RegisterPanel(QWidget* parent) : QWidget(parent)
{
	// 设置固定大小
	this->setFixedSize(400, 524);

	font = ResourceManager::getInstance()->getFontPool().find(ResID::Font_PingFang)->second;

	initTitle();
	initBody();
	initTail();

	connect(HttpManager::getInstance().get(), &HttpManager::signalRegModFinish, this, &RegisterPanel::slotRegModFinish);

	initHttpHandlers();
}

RegisterPanel::~RegisterPanel()
{
}

void RegisterPanel::slotRegModFinish(RequestID requestId, QString result, ErrorCodes error)
{
	if (error !=ErrorCodes::SUCCESS)
	{
		qDebug() << "网络请求错误!";
		return;
	}

	// 解析Json字符串, result转换为QByteArray
	QJsonDocument jsonDoc = QJsonDocument::fromJson(result.toUtf8());
	if (jsonDoc.isNull())
	{
		qDebug() << "Json解析失败!";
		return;
	}

	// Json解析错误
	if (!jsonDoc.isObject())
	{
		qDebug() << "Json解析失败!";
		return;
	}

	m_handlers[requestId](jsonDoc.object());
	return;
}

void RegisterPanel::initTitle()
{
	QLabel* regTitleLbl = new QLabel(this);
	regTitleLbl->setFixedSize(200, 50);
	font.setPixelSize(24);
	regTitleLbl->setFont(font);
	regTitleLbl->setText(u8"欢迎注册");
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
	userEdit->setPlaceholderText(u8"用户");

	QLineEdit* passwordEdit = new QLineEdit(body);
	passwordEdit->setFont(font);
	passwordEdit->setEchoMode(QLineEdit::Password);
	passwordEdit->setClearButtonEnabled(true);
	passwordEdit->setPlaceholderText(u8"密码");

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
	getBtn->setObjectName("getBtn");
	getBtn->setFixedSize(60, 35);
	font.setPixelSize(16);
	getBtn->setFont(font);
	getBtn->setText(u8"获取");
	getBtn->setCheckable(true);
	getBtn->setCursor(Qt::PointingHandCursor);
	connect(getBtn, &QPushButton::clicked, this, [=](){
		QString email = emailEdit->text();
		QRegularExpression regex(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
		bool match = regex.match(email).hasMatch();
		if (match)
		{
			// 发送验证码
		}
		else
		{
			// 提示邮箱地址不正确
		}
	});
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
	registerBtn->setText(u8"注册");
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
	loginBtn->setText(u8"密码登录");
	loginBtn->setCursor(Qt::PointingHandCursor);
	connect(loginBtn, &QPushButton::clicked, this, [=]() {
		emit sendLogin();
	});
	tailLayout->addWidget(loginBtn);
	tail->move((width() - tail->width()) / 2, (height() - tail->height()) * 15 / 16);
}

void RegisterPanel::initHttpHandlers()
{
	// 注册获取验证码回包的逻辑
	m_handlers.insert(RequestID::ID_GET_VARIFY_CODE, [this](const QJsonObject& jsonObj) {
		int error = jsonObj["error"].toInt();
		if (error != ErrorCodes::SUCCESS)
		{
			qDebug() << "参数错误!";
			return;
		}

		auto email = jsonObj["email"].toString();
		qDebug() << "验证码已经发送到邮箱，注意查收!";
		qDebug() << "email is:" << email;
	});
}
