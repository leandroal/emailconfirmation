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
    MessageHandler();
    virtual ~MessageHandler();
    bb::pim::message::MessageService* m_messageService;
    bb::pim::account::Account m_currentAccount;
    bb::platform::Notification m_notification;
    void confirmAccount(QString);
    QList<bb::pim::account::Account> m_accountList;
public Q_SLOTS:
    void onBodyDownloaded(bb::pim::account::AccountKey, bb::pim::message::MessageKey);
    void onMessagesAdded(bb::pim::account::AccountKey, QList<bb::pim::message::ConversationKey>, QList<bb::pim::message::MessageKey>);
    void onMessageAdded(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey);
    void onCodeReceived(int code);
private:
    NetworkManager m_networkManager;
};

#endif /* MESSAGEHANDLER_HPP_ */
