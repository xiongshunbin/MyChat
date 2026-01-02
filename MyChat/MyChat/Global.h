#pragma once

#include <QWidget>
#include <QStyle>
#include <QFontDatabase>
#include <QMap>
#include <functional>
#include <memory>
#include <mutex>

// 用来刷新QSS样式
extern std::function<void(QWidget*)> repolish;

enum RequestID
{
	ID_GET_VARIFY_CODE = 1001,	// 获取验证码
	ID_REGISTER_USER = 1002,	// 注册用户
};

enum Modules
{
	REGISTERMOD = 0
};

enum ErrorCodes {
	SUCCESS = 0,
	ERROR_JSON = 1,		// Json解析失败
	ERROR_NETWORK = 2,	// 网络错误
};
