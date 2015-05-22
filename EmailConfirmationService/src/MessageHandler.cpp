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
using namespace bb::platform;

MessageHandler::MessageHandler() :
        QObject(), m_messageService(new MessageService)
{

    m_messageService = new MessageService();

    bool ok = connect(m_messageService, SIGNAL(messagesAdded(bb::pim::account::AccountKey, QList<bb::pim::message::ConversationKey>, QList<bb::pim::message::MessageKey>)), this, SLOT(onMessagesAdded(bb::pim::account::AccountKey, QList<bb::pim::message::ConversationKey>, QList<bb::pim::message::MessageKey>)));
    Q_ASSERT(ok);
    ok = connect(m_messageService, SIGNAL(messageAdded(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey)), this, SLOT(onMessageAdded(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey)));
    Q_ASSERT(ok);
    ok = connect(m_messageService, SIGNAL(messageUpdated(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey, bb::pim::message::MessageUpdate)), this, SLOT(onMessageUpdated(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey, bb::pim::message::MessageUpdate)));
    Q_ASSERT(ok);

    NotificationDefaultApplicationSettings * settings = new NotificationDefaultApplicationSettings;
    settings->setPreview(bb::platform::NotificationPriorityPolicy::Allow);
    settings->apply();
    QStringList listAccounts;

    m_accountList = AccountService().accounts(Service::Messages);
    if (!m_accountList.isEmpty()) {
        m_currentAccount = m_accountList.first();
        for(int i = 0; i < m_accountList.size(); i++){
            listAccounts << m_accountList.at(i).displayName();
        }
    }
    QSettings settingsEmail("EmailConfirmation","listItem");
    settingsEmail.setValue("accounts", listAccounts);
    //filterMessages();
}

MessageHandler::~MessageHandler()
{
}

void MessageHandler::onMessageAdded(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey)
{
    qDebug() << "Messagehandler::filterMessages()";
    QSettings settingsEmail("EmailConfirmation", "listItem");
    if (!m_currentAccount.isValid()) {
        return;
    }
    QVariantMap entry; // The new email
    QString email_content;
    QVariantList emailsList; // List of old emails

    MessageSearchFilter filter;
    filter.addSearchCriteria(SearchFilterCriteria::FromAddress, "dielsonscarvalho@gmail.com");

    const QList<Message> messages = m_messageService->searchLocal(bb::pim::message::UndefinedKey, filter);
    foreach (Message msg, messages) {
        if (msg.isInbound()) {
            qDebug() << "Message is inbound:" << msg.subject();
        } else {
            qDebug() << "Message's not inboud:" << msg.subject();
        }
    }
    qDebug() << "settingsEmail.value('emailList') =" << settingsEmail.value("emailList");
    if (!(settingsEmail.value("emailList").toString().compare(QString("-1")) == 0)) {
        if (settingsEmail.value("emailList").canConvert(QVariant::List)) {
            emailsList = settingsEmail.value("emailList").toList();
        } else {
            emailsList.prepend(settingsEmail.value("emailList").toMap());
        }
        entry["messageId"] = messages.first().id();
        entry["subject"] = messages.first().subject();
        email_content = messages.first().body(MessageBody::PlainText).plainText();
        if (email_content.isEmpty()) {
            email_content = messages.first().body(MessageBody::Html).plainText();
        }
        entry["body"] = email_content;
        if (isNewEmail((qint64)messages.first().id(), emailsList)) {
            m_notification.setBody("A new confirmation email just arrived");
            m_notification.notify();
            emailsList.prepend(entry);
        } else {
            qDebug() << "It's not a new email";
        }
        activateAccount(entry);
    } else if (!(messages.isEmpty())) {
        entry["messageId"] = messages.first().id();
        entry["subject"] = messages.first().subject();
        email_content = messages.first().body(MessageBody::PlainText).plainText();
        if (email_content.isEmpty())
            email_content = messages.first().body(MessageBody::Html).plainText();
        entry["body"] = email_content;
        if (isNewEmail((qint64)messages.first().id(), emailsList)) {
            m_notification.setBody("A new confirmation email just arrived");
            m_notification.notify();
            emailsList.prepend(entry);
        } else {
            qDebug() << "It's not a new email";
        }
        activateAccount(entry);
    }
    settingsEmail.setValue("emailList", emailsList);
    settingsEmail.sync();
}

void MessageHandler::onMessageUpdated(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey, bb::pim::message::MessageUpdate) {
    // Do nothing meanwhile
}

void MessageHandler::onMessagesAdded(bb::pim::account::AccountKey, QList<bb::pim::message::ConversationKey>, QList<bb::pim::message::MessageKey>) {
    // Do nothing meanwhile
}

void MessageHandler::activateAccount(QVariantMap mailInformation){
    Q_UNUSED(mailInformation);
/*
 *  Put here your code to automatically activate the email
 *  With the variable mailInformation you can get all information from your email confirmation (mailInformation.id,mailInformation.subject,mailInformation.body(MessageBody::PlainText).plainText())
 *  With QNetworkAccessManager for example, you can do a POST to your web server and auto activate the account of the new user.
 */
}

// Private ----------------------------------------------------------

/**
 * Returns true if emailId is not among emailsList
 */
bool MessageHandler::isNewEmail(qint64 emailId, const QVariantList & emailsList) {
    int isNew = true;
    foreach (QVariant email, emailsList) {
        bool ok;
        qint64 id = email.toMap()["messageId"].toInt(&ok);
        if (id == emailId) {
            qDebug() << "Found a matching id. Email is not new.";
            isNew = false;
        }
    }
    return isNew;
}
