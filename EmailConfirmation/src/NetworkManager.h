/*
 * NetworkManager.h
 *
 *  Created on: 21/05/2015
 *      Author: dielson
 */

#ifndef NETWORKMANAGER_H_
#define NETWORKMANAGER_H_

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStack>

class NetworkManager: public QObject
{
    Q_OBJECT
public:
    static QUrl ACCOUNT_URL;
    NetworkManager();
    virtual ~NetworkManager();
    Q_INVOKABLE void submit(QString name, QString email, QString password);
public slots:
    void onFinished(QNetworkReply*);
private:
    QNetworkAccessManager m_netManager;
};

#endif /* NETWORKMANAGER_H_ */
