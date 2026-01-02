#pragma once

#include "SingletonBase.h"
#include <QString>
#include <QUrl>
#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>

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
