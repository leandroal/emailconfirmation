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

#include "MessageHandler.hpp"
#include <bb/pim/account/AccountService>
#include <bb/pim/account/Provider>
#include <bb/pim/message/MessageSearchFilter>
#include <QList>
#include <QSettings>
#include <QVariant>
#include <QMap>
#include <QSettings>

using namespace bb::pim::message;
using namespace bb::cascades;
using namespace bb::pim::account;
using namespace bb::platform;

QRegExp MessageHandler::URL_PARSER = QRegExp("https?:"
        "(?://((?:(([^/?#@: \n\t]*)(?::([^/?#@ \n\t]*))?)@)?"
        "([^/?#: \n\t]*)(?::([^/?# \n\t]*))?))?"
        "([^?# \n\t]*)"
        "(?:\\?((?:\\S)*))?");

QString MessageHandler::DEFAULT_EMAIL = QString("emailconfirmation@compelab.org");

MessageHandler::MessageHandler() :
        QObject(), m_messageService(new MessageService)
{
    bool ok = connect(m_messageService, SIGNAL(messageAdded(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey)), this, SLOT(onMessageAdded(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey)));
    Q_ASSERT(ok);
    ok = connect(m_messageService, SIGNAL(bodyDownloaded(bb::pim::account::AccountKey, bb::pim::message::MessageKey)), this, SLOT(onBodyDownloaded(bb::pim::account::AccountKey, bb::pim::message::MessageKey)));
    Q_ASSERT(ok);
    ok = connect(&m_networkManager, SIGNAL(confirmationCode(int)), this, SLOT(onCodeReceived(int)));
    Q_ASSERT(ok);

    NotificationDefaultApplicationSettings * settings = new NotificationDefaultApplicationSettings;
    settings->setPreview(bb::platform::NotificationPriorityPolicy::Allow);
    settings->apply();

    // Also possible to pass "popemail" as argument if you wanna monitor POP messages
    m_accountList = AccountService().accounts(Service::Messages, "imapemail");
    if (!m_accountList.isEmpty()) {
        m_currentAccount = m_accountList.first();
    }
}

MessageHandler::~MessageHandler()
{
}

void MessageHandler::onMessageAdded(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey)
{
}

void MessageHandler::onBodyDownloaded(bb::pim::account::AccountKey accountId, bb::pim::message::MessageKey messageKey)
{
    if (!m_currentAccount.isValid()) {
        return;
    }
    Message msg = m_messageService->message(accountId, messageKey);
    if (msg.isInbound()) {
        if (msg.sender().address() == DEFAULT_EMAIL) {
            QString emailContent = msg.body(MessageBody::PlainText).plainText();
            if (emailContent.isEmpty()) {
                emailContent = msg.body(MessageBody::Html).plainText();
            }
            m_notification.setBody("A new confirmation email just arrived");
            m_notification.notify();

            confirmAccount(emailContent);
        }
    }
}

void MessageHandler::confirmAccount(QString content){
    qDebug() << "Confirming...";
    QRegExp x = URL_PARSER;
    int pos = x.lastIndexIn(content);
    QString matchingString;
    matchingString = x.cap();
    QUrl url(matchingString);
    Q_ASSERT(url.isValid());
    m_networkManager.confirm(url);
}

void MessageHandler::onCodeReceived(int code) {
    if (code == 1) {
        QSettings settings("EmailConfirmation","listItem");
        settings.setValue("accountStatus", QString("Account [email] confirmed"));
    }
}
