/*
 * NetworkManager.cpp
 *
 *  Created on: 21/05/2015
 *      Author: dielson
 */

#include <QDebug>

#include "NetworkManager.h"

QUrl NetworkManager::ACCOUNT_URL = QUrl("http://www.compelab.org/emailconfirmation/");

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::submit(QString name, QString email, QString password) {
    qDebug() << "NetworkManager::submit(email=" << email << ", password=" << password << ");";
    bool connected = connect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(connected);
    QNetworkRequest request(ACCOUNT_URL);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QUrl parameters;
    parameters.addQueryItem("name", name);
    parameters.addQueryItem("email", email);
    parameters.addQueryItem("password", password);
    m_netManager.post(request, parameters.encodedQuery());
}

void NetworkManager::onFinished(QNetworkReply* reply) {
    bool disconnected = disconnect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(disconnected);
    reply->deleteLater();
}
