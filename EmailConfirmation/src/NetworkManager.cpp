/*
 * NetworkManager.cpp
 *
 *  Created on: 21/05/2015
 *      Author: dielson
 */

#include "NetworkManager.h"

QUrl NetworkManager::ACCOUNT_URL = QUrl("http://compelab.org/emailconfirmation/confirm");

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::createAccount(QString email, QString password) {
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
    if (reply->request().url() == ACCOUNT_URL) {
        // do something
    }
    reply->deleteLater();
}
