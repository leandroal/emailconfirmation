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

class NetworkManager
{
public:
    NetworkManager();
    virtual ~NetworkManager();
};

#endif /* NETWORKMANAGER_H_ */
