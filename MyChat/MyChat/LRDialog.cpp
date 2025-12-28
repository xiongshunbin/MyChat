#include <QIcon>
#include <QVBoxLayout>
#include <QtWinExtras/QtWin>
#include "LRDialog.h"

#ifdef Q_OS_WIN
#include <Dwmapi.h>  // Use system shadow frame
#pragma comment(lib, "dwmapi.lib")
#endif

LRDialog::LRDialog(QWidget* parent) : QWidget(parent)
{
	// 设置固定大小
	this->setFixedSize(400, 560);

	// 设置应用图标
	this->setWindowIcon(QIcon(":/MyChat.ico"));

	// 去除系统边框
	this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

	// 调用win系统api设置窗口阴影
#ifdef Q_OS_WIN 
	BOOL bEnable = false;
	::DwmIsCompositionEnabled(&bEnable);
	if (bEnable)
	{
		DWMNCRENDERINGPOLICY ncrp = DWMNCRP_ENABLED;
		::DwmSetWindowAttribute((HWND)winId(), DWMWA_NCRENDERING_POLICY, &ncrp, sizeof(ncrp));
		MARGINS margins = { -1 };
		::DwmExtendFrameIntoClientArea((HWND)winId(), &margins);
	}

	HWND hwnd = reinterpret_cast<HWND>(this->winId());
	DWORD style = GetWindowLong(hwnd, GWL_STYLE);
	SetWindowLongPtr(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
#endif

	// 设置窗体背景
	this->setObjectName("LRDialog");

	QWidget* topBar = initTopBar();

	stackWidget = new QStackedWidget;

	loginDialog = new LoginPanel(this);
	connect(loginDialog, &LoginPanel::sendRegister, this, [=]() {
		stackWidget->setCurrentIndex(1);
	});

	connect(loginDialog, &LoginPanel::sendForget, this, [=]() {
		stackWidget->setCurrentIndex(2);
	});

	registerDialog = new RegisterPanel(this);
	connect(registerDialog, &RegisterPanel::sendLogin, this, [=]() {
		stackWidget->setCurrentIndex(0);
	});

	forgetDialog = new ForgetPasswordPanel(this);
	connect(forgetDialog, &ForgetPasswordPanel::sendRegister, this, [=]() {
		stackWidget->setCurrentIndex(1);
	});

	stackWidget->addWidget(loginDialog);
	stackWidget->addWidget(registerDialog);
	stackWidget->addWidget(forgetDialog);

	QVBoxLayout* layout = new QVBoxLayout;
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(topBar);
	layout->addWidget(stackWidget);
	this->setLayout(layout);

	stackWidget->setCurrentIndex(0);
}

LRDialog::~LRDialog()
{

}

QWidget* LRDialog::initTopBar()
{
	QWidget* topBar = new QWidget(this);
	topBar->setFixedSize(width(), 36);
	topBar->setContentsMargins(0, 0, 0, 0);
	QHBoxLayout* topLayout = new QHBoxLayout(topBar);
	topLayout->setContentsMargins(0, 0, 0, 0);
	topLayout->setSpacing(0);

	// 关闭按钮
	QPushButton* closeBtn = new QPushButton(topBar);
	closeBtn->setFixedSize(40, 36);
	closeBtn->setObjectName("closeBtn");
	QFont iconFont = ResourcesManager::instance()->getFontPool().find(ResID::Font_TitleBar_iconfont)->second;
	iconFont.setPixelSize(14);
	closeBtn->setFont(iconFont);
	closeBtn->setText(QChar(0xe652));
	connect(closeBtn, &QPushButton::clicked, this, [=]() {
		this->close();
		});

	// 最小化按钮
	QPushButton* minBtn = new QPushButton(topBar);
	minBtn->setFixedSize(30, 36);
	minBtn->setObjectName("minBtn");
	iconFont.setPixelSize(15);
	minBtn->setFont(iconFont);
	minBtn->setText(QChar(0xe650));
	connect(minBtn, &QPushButton::clicked, this, [=]() {
		this->showMinimized();
		});

	topLayout->addStretch();
	topLayout->addWidget(minBtn);
	topLayout->addWidget(closeBtn);
	topBar->move(0, 0);
	return topBar;
}

void LRDialog::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		leftPressed = true;
		windowPos = this->pos();			// 记录当前窗体左上角的坐标
		pressPos = event->globalPos();		// 记录鼠标按下的位置
	}
}

void LRDialog::mouseMoveEvent(QMouseEvent* event)
{
	if (leftPressed)
		this->move(event->globalPos() + windowPos - pressPos);
}

void LRDialog::mouseReleaseEvent(QMouseEvent* event)
{
	leftPressed = false;
}

// 通过拦截消息重新去掉标题栏
bool LRDialog::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
	if (eventType != "windows_generic_MSG")
		return false;

	MSG* msg = static_cast<MSG*>(message);

	if (msg->message == WM_NCCALCSIZE) {
		*result = 0;
		return true;
	}

	return QWidget::nativeEvent(eventType, message, result);
}
