/* E-mail confirmation sample for BlackBerry 10 - Client side
 * Copyright (C) <2015> Dielson Carvalho <dielson.carvalho@compelab.org>
 * Copyright (C) <2015> Leandro Melo de Sales <leandro@compelab.org>
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU. Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this code; if not, write to the


 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <QDebug>
#include <bb/data/JsonDataAccess>

#include "NetworkManager.h"

QUrl NetworkManager::ACCOUNT_URL = QUrl("http://www.compelab.org/ec/scripts/storeuser.php");

NetworkManager::NetworkManager()
{
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::submit(QString name, QString email, QString password) {
    bool connected = connect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(connected);
    QNetworkRequest request(ACCOUNT_URL);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QUrl parameters;
    parameters.addQueryItem("name", name);
    parameters.addQueryItem("email", email);
    m_netManager.post(request, parameters.encodedQuery());
}

void NetworkManager::onFinished(QNetworkReply* reply) {
    using namespace bb::data;
    bool disconnected = disconnect(&m_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    Q_ASSERT(disconnected);
    if (reply->error() == QNetworkReply::NoError) {
        JsonDataAccess json;
        QString contentString = reply->readAll();
        qDebug() << "POST reply:" << contentString;
        QVariantMap content = json.loadFromBuffer(contentString).toMap();
        bool ok;
        int replyCode = content["id"].toInt(&ok);
        if (!ok) replyCode = -1;
        if (replyCode == 0) {
            emit emailSent();
        }
    }
    reply->deleteLater();
}
