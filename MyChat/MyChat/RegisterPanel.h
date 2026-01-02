#pragma once

#include "Global.h"

class RegisterPanel : public QWidget
{
	Q_OBJECT
public:
	explicit RegisterPanel(QWidget* parent = nullptr);
	~RegisterPanel();

public slots:
	void slotRegModFinish(RequestID requestId, QString result, ErrorCodes error);

protected:
	void initTitle();
	void initBody();
	void initTail();

private:
	void initHttpHandlers();

signals:
	void sendLogin();

private:
	QFont font;
	QMap<RequestID, std::function<void(const QJsonObject&)>> m_handlers;
};
