#include "applicationheadless.hpp"

#include <bb/Application>
#include <bb/device/Led>
#include <bb/device/LedColor>
#include <bb/system/InvokeManager>
#include <bb/system/InvokeRequest>
#include <QDebug>


using namespace bb::device;
using namespace bb::system;


ApplicationHeadless::ApplicationHeadless()
    : QObject()
    , m_invokeManager(new InvokeManager(this))
{
    QMetaObject::invokeMethod(this, "init", Qt::QueuedConnection);
}

void ApplicationHeadless::onInvoked(const bb::system::InvokeRequest& request)
{
    if (request.action().compare("bb.action.system.STARTED") == 0) {

    }

    if (request.action().compare("bb.action.email.RECEIVED") == 0) {
        // ??
    }
    if (request.action().compare("teste") == 0) {
        m_messagehandler.filterMessages();
    }

}


void ApplicationHeadless::init()
{

}

