/*
 * MessageHandler.cpp
 *
 *  Created on: 30/03/2015
 *      Author: gualberto
 */
#include "MessageHandler.hpp"
#include <bb/pim/account/AccountService>
#include <bb/pim/message/MessageSearchFilter>
#include <QList>
#include <QSettings>
#include <QVariant>
#include <QMap>
#include <QSettings>
using namespace bb::pim::message;
using namespace bb::cascades;
using namespace bb::pim::account;


MessageHandler::MessageHandler() :
        QObject(), m_messageService(new MessageService)
{

    m_messageService = new MessageService();

    bool ok =
            connect(m_messageService,
                    SIGNAL(
                            messagesAdded(bb::pim::account::AccountKey, QList<bb::pim::message::ConversationKey>, QList<bb::pim::message::MessageKey>)),
                    SLOT(filterMessages()));
    Q_ASSERT(ok);
    ok =
            connect(m_messageService,
                    SIGNAL(
                            messageAdded(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey)),
                    SLOT(filterMessages()));
    Q_ASSERT(ok);
    ok =
            connect(m_messageService,
                    SIGNAL(
                            messageUpdated(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey, bb::pim::message::MessageUpdate)),
                    SLOT(filterMessages()));
    Q_ASSERT(ok);
    ok =
            connect(m_messageService,
                    SIGNAL(
                            messageRemoved(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey, QString)),
                    SLOT(filterMessages()));
    Q_ASSERT(ok);

    bb::platform::NotificationDefaultApplicationSettings * settings =
            new bb::platform::NotificationDefaultApplicationSettings;
    settings->setPreview(bb::platform::NotificationPriorityPolicy::Allow);
    settings->apply();
    QStringList listAccounts;

    m_accountList = AccountService().accounts(Service::Messages);
    if (!m_accountList.isEmpty()) {
        m_currentAccount = m_accountList.first();
      //  qDebug() << m_accountList.size();
        for(int i = 0; i < m_accountList.size(); i++){
        listAccounts << m_accountList.at(i).displayName();
        }

    }
    //qDebug() << listAccounts;
    QSettings settingsEmail("EmailConfirmation","listItem");
    settingsEmail.setValue("accounts", listAccounts);
    //filterMessages();



}

MessageHandler::~MessageHandler()
{

}

void MessageHandler::filterMessages()
{
    QSettings settingsEmail("EmailConfirmation","listItem");
    if (!m_currentAccount.isValid())
        return;

    QString m_body;
    QVariantMap entry;
    MessageSearchFilter filter;
    QVariantList emailList;
    filter.addSearchCriteria(SearchFilterCriteria::FromAddress,
            "automailconfirmationblackberry@gmail.com");

    const QList<Message> messages = m_messageService->searchLocal(bb::pim::message::UndefinedKey, filter);
    qDebug() << settingsEmail.value("emailList");
    if(!(settingsEmail.value("emailList").toString().compare(QString("-1")) == 0)){
        qDebug()<< "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        if (settingsEmail.value("emailList").canConvert(QVariant::List)){
            qDebug()<< "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
    emailList = settingsEmail.value("emailList").toList(); //TODO mudar nome historic

        }

        else{
            qDebug()<< "ccccccccccccccccccccccccccccccccccccccc";
            emailList.prepend(settingsEmail.value("emailList").toMap());
        }

            entry["messageId"] = messages.first().id();
            entry["subject"] = messages.first().subject();
            m_body = messages.first().body(MessageBody::PlainText).plainText();
            if (m_body.isEmpty())
                m_body = messages.first().body(MessageBody::Html).plainText();
            entry["body"] = m_body;
            m_notification.setBody("A new Confirmation Email just arrived");
            m_notification.notify();
            emailList.prepend(entry);
            activateAccount(entry);

            qDebug()<< "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee";


    }
    else{
        if(!(messages.isEmpty())){
            qDebug()<< "fffffffffffffffffffffffffffffffffff";
            entry["messageId"] = messages.first().id();
            entry["subject"] = messages.first().subject();
            m_body = messages.first().body(MessageBody::PlainText).plainText();
            if (m_body.isEmpty())
                m_body = messages.first().body(MessageBody::Html).plainText();
            entry["body"] = m_body;
            m_notification.setBody("A new Confirmation Email just arrived");
            m_notification.notify();
            emailList.prepend(entry);
            activateAccount(entry);




        }
    }


//    foreach (const Message &message, messages) {
//
//        QVariantMap entry;
//        entry["messageId"] = message.id();
//        entry["subject"] = message.subject();
//        entry["time"] = message.serverTimestamp().toString();
//        m_body = message.body(MessageBody::PlainText).plainText();
//        if (m_body.isEmpty())
//            m_body = message.body(MessageBody::Html).plainText();
//        entry["body"] = m_body;
//
//
//  //      qDebug() << message.subject();

//
//    }
    settingsEmail.setValue("emailList", emailList);



}

void MessageHandler::activateAccount(QVariantMap mailInformation){
/*
 * Put here your code to automatically activate the email
 *
 *  With the variable mailInformation you can get all information from your email confirmation (mailInformation.id,mailInformation.subject,mailInformation.body(MessageBody::PlainText).plainText())
 *
 *  With QNetworkAccessManager for example, you can do a POST to your web server and auto activate the account of the new user.
 *
 *
 *
 *
 */
}
