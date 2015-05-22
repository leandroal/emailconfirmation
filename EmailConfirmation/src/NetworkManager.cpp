/*
 * NetworkManager.cpp
 *
 *  Created on: 21/05/2015
 *      Author: dielson
 */

#include <QDebug>

#include "NetworkManager.h"

QUrl NetworkManager::ACCOUNT_URL = QUrl("http://compelab.org/emailconfirmation/confirm");

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::submit(QString email, QString password) {
    qDebug() << "NetworkManager::submit(email=" << email << ", password=" << password << ");";
    bool connected = connect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(connected);
    QNetworkRequest request(ACCOUNT_URL);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QUrl parameters;
    parameters.addQueryItem("email", email);
    parameters.addQueryItem("password", password);
    m_netManager.post(request, parameters.encodedQuery());
}

void NetworkManager::onFinished(QNetworkReply* reply) {
    bool disconnected = disconnect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(disconnected);
    if (reply->request().url() == ACCOUNT_URL) {
        qDebug() << "Reply url match the request";
        qDebug() << "Error was" << reply->errorString();
    } else {
        QString lastUrl = m_urls.pop();
        Q_ASSERT(reply->request().url() == QUrl(lastUrl)); // just to make sure
        qWarning() << "Reply url doesn't match the request!!!";
        qDebug() << "Error was" << reply->errorString();
    }
    reply->deleteLater();
}
