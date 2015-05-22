#ifndef MESSAGEHANDLER_HPP_
#define MESSAGEHANDLER_HPP_
#include <QObject>
#include <bb/cascades/GroupDataModel>
#include <bb/pim/account/Account>
#include <bb/pim/message/MessageService>
#include <bb/platform/Notification>
#include <bb/platform/NotificationDefaultApplicationSettings>

class MessageHandler : public QObject
{
    Q_OBJECT
public:
    MessageHandler();
    virtual ~MessageHandler();
    bb::pim::message::MessageService* m_messageService;
    bb::pim::account::Account m_currentAccount;
    bb::platform::Notification m_notification;
    void activateAccount(QVariantMap);
    QList<bb::pim::account::Account> m_accountList;
public Q_SLOTS:
    void onMessagesAdded(bb::pim::account::AccountKey, QList<bb::pim::message::ConversationKey>, QList<bb::pim::message::MessageKey>);
    void onMessageAdded(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey);
    void onMessageUpdated(bb::pim::account::AccountKey, bb::pim::message::ConversationKey, bb::pim::message::MessageKey, bb::pim::message::MessageUpdate);
//    void checkEmail(bb::pim::message::MessageKey);
//    void checkManyEmails(bb::pim::account::AccountKey, QList<bb::pim::message::ConversationKey>, QList<bb::pim::message::MessageKey>);
private:
    bool isNewEmail(qint64 emailId, const QVariantList & emailsList);
};

#endif /* MESSAGEHANDLER_HPP_ */
