#include <QDebug>

#include "NetworkManager.h"

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::confirm(QString url) {
    qDebug() << "NetworkManager::confirm(url=" << url << ");";
    bool connected = connect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(connected);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    m_netManager.get(request);
}

void NetworkManager::onFinished(QNetworkReply* reply) {
    bool disconnected = disconnect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(disconnected);
    // check if was confirmed
    reply->deleteLater();
}
