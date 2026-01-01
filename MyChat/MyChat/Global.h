#pragma once

#include <QWidget>
#include <functional>
#include <QStyle>

// 用来刷新QSS样式
extern std::function<void(QWidget*)> repolish;
