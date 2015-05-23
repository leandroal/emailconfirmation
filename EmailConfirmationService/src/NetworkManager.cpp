#include <QDebug>

#include "NetworkManager.h"

#include <bb/data/JsonDataAccess>

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::confirm(QUrl url) {
    qDebug() << "NetworkManager::confirm(url=" << url << ");";
    bool connected = connect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(connected);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_netManager.get(request);
}

void NetworkManager::onFinished(QNetworkReply* reply) {
    using namespace bb::data;
    bool disconnected = disconnect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(disconnected);
    if (reply->error() == QNetworkReply::NoError) {
        JsonDataAccess json;
        QString contentString = reply->readAll();
        qDebug() << "contentString =" << contentString;
        QVariantMap content = json.load(contentString).toMap();
        int replyCode = content["id"].toInt();
        emit confirmationCode(replyCode);
    }

    reply->deleteLater();
}
