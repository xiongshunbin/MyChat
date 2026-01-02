#include "HttpManager.h"
#include <QByteArray>
#include <QNetworkReply>
#include <QDebug>

HttpManager::HttpManager()
{
	connect(this, &HttpManager::signalHttpFinish, this, &HttpManager::slotHttpFinish);
}

void HttpManager::httpPostRequest(QUrl url, QJsonObject json, RequestID requestId, Modules module)
{
	QByteArray data = QJsonDocument(json).toJson();
	QNetworkRequest request(url);
	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
	request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(data.length()));
	auto self = shared_from_this();		// 闭包
	QNetworkReply* reply = m_manager.post(request, data);
	connect(reply, &QNetworkReply::finished, [self, reply, requestId, module]() {
		// 处理错误情况
		if (reply->error() != QNetworkReply::NoError)
		{
			qDebug() << reply->errorString();
			// 发送信号通知完成
			emit self->signalHttpFinish(requestId, "", ErrorCodes::ERROR_NETWORK, module);
			reply->deleteLater();
			return;
		}

		// 正确
		QString result = reply->readAll();
		// 发送信号通知完成
		emit self->signalHttpFinish(requestId, result, ErrorCodes::SUCCESS, module);
		reply->deleteLater();
		return;
	});
}

HttpManager::~HttpManager()
{
}

void HttpManager::slotHttpFinish(RequestID requestId, QString result, ErrorCodes error, Modules module)
{
	if (module == Modules::REGISTERMOD) {
		// 发送信号通知指定模块HTTP的响应结束
		emit signalRegModFinish(requestId, result, error);
	}
}
