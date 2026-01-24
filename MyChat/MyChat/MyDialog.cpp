#include "MyDialog.h"

MyDialog* MyDialog::m_myDialog = nullptr;

MyDialog::MyDialog(QWidget* parent) : CustomDialog(parent)
{
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
 
	QVBoxLayout* Layout = new QVBoxLayout(this);
	Layout->setMargin(0);
	Layout->addStretch();
	QHBoxLayout* centerLayout = new QHBoxLayout;
	centerLayout->setMargin(0);
	Layout->addLayout(centerLayout);
	Layout->addStretch();

	centerLayout->addStretch();
	mainDialog = new QWidget(this);
	this->setMainDialog(mainDialog);
	mainDialog->setObjectName("mainDialog");
	mainDialog->setFixedSize(mainDialog_w, mainDialog_h);
	centerLayout->addWidget(mainDialog);
	centerLayout->addStretch();

	QVBoxLayout* CVLayout = new QVBoxLayout(mainDialog);
	CVLayout->setContentsMargins(20, 0, 0, 25);
	CVLayout->setSpacing(0);
	QWidget* top = new QWidget(mainDialog);
	top->setFixedHeight(30);
	QHBoxLayout* topHLayout = new QHBoxLayout(top);
	topHLayout->setMargin(0);
	topHLayout->SetFixedSize;
	btnClose = new QPushButton(top);
	btnClose->setObjectName("btnClose");
	btnClose->installEventFilter(this);
	btnClose->setFixedSize(30, 30);
	QFont iconFont = ResourceManager::getInstance()->getFontPool().find(ResID::Font_TitleBar_iconfont)->second;
	iconFont.setPixelSize(16);
	btnClose->setFont(iconFont);
	btnClose->setText(QChar(0xe652));
	connect(btnClose, &QPushButton::clicked, this, &CustomDialog::closeDialog);
	topHLayout->addStretch();
	topHLayout->addWidget(btnClose);
	CVLayout->addWidget(top);
	QFont font = ResourceManager::getInstance()->getFontPool().find(ResID::Font_PingFang)->second;
	font.setPixelSize(18);
	lblMessage = new QLabel(mainDialog);
	lblMessage->setObjectName("lblMessage");
	lblMessage->setAlignment(Qt::AlignTop);
	lblMessage->setMargin(0);
	lblMessage->setFont(font);
	lblMessage->setWordWrap(true);
	CVLayout->addWidget(lblMessage);
	QWidget* tail = new QWidget(mainDialog);
	tail->setFixedHeight(40);
	QHBoxLayout* tailHLayout = new QHBoxLayout(tail);
	tailHLayout->setSpacing(10);
	tailHLayout->setContentsMargins(0, 0, 20, 0);
	QPushButton* btnForgetPassword = new QPushButton(tail);
	btnForgetPassword->setObjectName("btnForgetPassword");
	btnForgetPassword->setFixedSize(100, 40);
	btnForgetPassword->setFont(font);
	btnForgetPassword->setText(u8"忘记密码");
	QPushButton* btnReLogin = new QPushButton(tail);
	btnReLogin->setObjectName("btnReLogin");
	btnReLogin->setFixedSize(100, 40);
	btnReLogin->setFont(font);
	btnReLogin->setText(u8"重新登录");
	tailHLayout->addStretch();
	tailHLayout->addWidget(btnForgetPassword);
	tailHLayout->addWidget(btnReLogin);
	CVLayout->addWidget(tail);

	this->setStyleSheet(ResourceManager::getInstance()->getStylePool().find(ResID::Style_MyDialog)->second);

	connect(btnForgetPassword, &QPushButton::clicked, this, &CustomDialog::closeDialog);
	connect(btnReLogin, &QPushButton::clicked, this, &CustomDialog::closeDialog);
}

MyDialog::~MyDialog()
{

}

void MyDialog::exec(QWidget* parent)
{
	setParent(parent);
	setGeometry(parent->rect());
	update();
	CustomDialog::showDialog();
}

void MyDialog::setMessage(QString message)
{
	QString showMessage = "<p style='line-height:35px; '>" + message + "</p>";
	lblMessage->setText(showMessage);
}

void MyDialog::setDialogSize(int w, int h)
{
	mainDialog_w = w;
	mainDialog_h = h;
	mainDialog->setFixedSize(mainDialog_w, mainDialog_h);
}

bool MyDialog::eventFilter(QObject* watched, QEvent* event)
{
	if (watched = btnClose)
	{
		if(event->type() == QEvent::Enter)
			this->setCursor(Qt::PointingHandCursor);
		else if (event->type() == QEvent::Leave)
			this->setCursor(Qt::ArrowCursor);
	}
	return QWidget::eventFilter(watched, event);
}
