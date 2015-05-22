#ifndef ApplicationHeadless_HPP_
#define ApplicationHeadless_HPP_

#include <QObject>
#include <QFileSystemWatcher>
#include "MessageHandler.hpp"
#include "NetworkManager.h"


namespace bb
{
    namespace system
    {
        class InvokeManager;
        class InvokeRequest;
    }
}


class ApplicationHeadless: public QObject
{
    Q_OBJECT
public:
    ApplicationHeadless();
    virtual ~ApplicationHeadless()
    {
    }

public Q_SLOTS:

    void onInvoked(const bb::system::InvokeRequest& request);
    void init();

private:
    // Invocation Manager instance for receiving system events
    bb::system::InvokeManager *m_invokeManager;
    MessageHandler m_messagehandler;
    NetworkManager m_networkManager;

    static const QString m_author; // for creating settings
    static const QString m_appName; // for creating settings
};

#endif /* ApplicationHeadless_HPP_ */
