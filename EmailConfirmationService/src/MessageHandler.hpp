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

#ifndef MESSAGEHANDLER_HPP_
#define MESSAGEHANDLER_HPP_
#include <QObject>
#include <bb/cascades/GroupDataModel>
#include <bb/pim/account/Account>
#include <bb/pim/message/MessageService>
#include <bb/platform/Notification>
#include <bb/platform/NotificationDefaultApplicationSettings>

#include "NetworkManager.h"

class MessageHandler : public QObject
{
    Q_OBJECT
public:
    static QRegExp URL_PARSER;
    static QString DEFAULT_EMAIL;
    MessageHandler();
    virtual ~MessageHandler();
    bb::pim::message::MessageService* m_messageService;
    bb::pim::account::Account m_currentAccount;
    bb::platform::Notification m_notification;
    void confirmAccount(QString);
    QList<bb::pim::account::Account> m_accountList;
public Q_SLOTS:
    void onBodyDownloaded(bb::pim::account::AccountKey, bb::pim::message::MessageKey);
    void onMessageAdded(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey);
    void onCodeReceived(int code);
private:
    NetworkManager m_networkManager;
};

#endif /* MESSAGEHANDLER_HPP_ */
