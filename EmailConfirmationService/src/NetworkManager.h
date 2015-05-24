/* E-mail confirmation sample for BlackBerry 10 - Client side
 * Copyright (C) <2015> Dielson Carvalho <dielson.carvalho@compelab.org>
 * Copyright (C) <2015> Durval Pereira <durval@compelab.org>
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

#ifndef NETWORKMANAGER_H_
#define NETWORKMANAGER_H_

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class NetworkManager: public QObject
{
    Q_OBJECT
public:
    NetworkManager();
    virtual ~NetworkManager();
    void confirm(QUrl url);
signals:
    void confirmationCode(int code);
public slots:
    void onFinished(QNetworkReply*);
private:
    QNetworkAccessManager m_netManager;
};

#endif /* NETWORKMANAGER_H_ */
