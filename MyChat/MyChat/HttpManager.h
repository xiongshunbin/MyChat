#pragma once

#include "SingletonBase.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

enum RequestID
{
	ID_GET_VARIFY_CODE = 1001,	// ªÒ»°—È÷§¬Î
	ID_REGISTER_USER = 1002,
};

enum Modules
{
	REGISTERMOD = 0
};

enum ErrorCodes {
	SUCCESS = 0,
	ERROR_JSON = 1,		// JsonΩ‚Œˆ ß∞‹
	ERROR_NETWORK = 2,	// Õ¯¬Á¥ÌŒÛ
};

// CRTP(∆Ê“Ïµ›πÈƒ£∞Â)

class HttpManager : public QObject, public SingletonBase<HttpManager>, 
	public std::enable_shared_from_this<HttpManager>
{
	Q_OBJECT
public:
	~HttpManager();

private slots:
	void slotHttpFinish(RequestID requestId, QString result, ErrorCodes error, Modules module);

signals:
	void signalHttpFinish(RequestID requestId, QString result, ErrorCodes error, Modules module);
	void signalRegModFinish(RequestID requestId, QString result, ErrorCodes error);

private:
	HttpManager();
	void httpPostRequest(QUrl url, QJsonObject json, RequestID requestId, Modules module);

private:
	friend class SingletonBase<HttpManager>;

	QNetworkAccessManager m_manager;
};
