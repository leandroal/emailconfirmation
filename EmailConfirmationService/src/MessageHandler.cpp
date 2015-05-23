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
    ok = connect(&m_networkManager, SIGNAL(confirmationCode(int)), this, SLOT(onCodeReceived(int)));

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

void MessageHandler::onMessageAdded(bb::pim::account::AccountKey accountKey, bb::pim::message::ConversationKey conversationKey, bb::pim::message::MessageKey messageKey)
{
    qDebug() << "Messagehandler::filterMessages()";
    // QSettings settingsEmail("EmailConfirmation", "listItem");
    if (!m_currentAccount.isValid()) {
        return;
    }
    MessageSearchFilter filter;
    filter.addSearchCriteria(SearchFilterCriteria::FromAddress, "emailconfirmation@compelab.org");

    const QList<Message> messages = m_messageService->searchLocal(bb::pim::message::UndefinedKey, filter);
    foreach (Message msg, messages) {
        if (msg.isInbound() && msg.id() == messageKey) {
            qDebug() << "Message inbound:" << msg.subject();
            QString emailContent = msg.body(MessageBody::Html).plainText();
            qDebug() << "This is between";
            qDebug() << "email content is" << msg.body(MessageBody::Html).plainText();
//            if (emailContent.isEmpty()) {
//                emailContent = msg.body(MessageBody::Html).plainText();
//            }
            m_notification.setBody("A new confirmation email just arrived");
            m_notification.notify();

            confirmAccount(emailContent);
        }
    }
}

void MessageHandler::onMessagesAdded(bb::pim::account::AccountKey, QList<bb::pim::message::ConversationKey>, QList<bb::pim::message::MessageKey>) {
    // Do nothing meanwhile

}

void MessageHandler::confirmAccount(QString content){
    qDebug() << "Confirming...";
    QStringList lists = content.split(" ");
    foreach (QString s, lists) {
        qDebug() << "testing" << s;
        if (s.startsWith("http")) {
            qDebug() << "URL is" << s;
            m_networkManager.confirm(s);
        }
    }
}

void MessageHandler::onCodeReceived(int code) {
    if (code == 1) {
        QSettings settings("EmailConfirmation","listItem");
        settings.setValue("accountStatus", QString("Account confirmed"));
        qDebug() << ">>> Account confirmed!";
        settings.sync();
    }
}
