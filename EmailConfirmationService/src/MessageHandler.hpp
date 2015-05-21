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
    void filterMessages();
};

#endif /* MESSAGEHANDLER_HPP_ */
