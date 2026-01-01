#include "Global.h"

std::function<void(QWidget*)> replolish = [](QWidget* widget) {
	widget->style()->unpolish(widget);
	widget->style()->polish(widget);
};
