/* Copyright (c) 2013 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ApplicationHeadless_HPP_
#define ApplicationHeadless_HPP_

#include <QObject>
#include <QFileSystemWatcher>
#include "MessageHandler.hpp"


namespace bb
{
    namespace system
    {
        class InvokeManager;
        class InvokeRequest;
    }
    namespace device
    {
        class Led;
    }
}

/*!
 * @brief Class which represents the headless service
 * 	      that initializes a Led object and starts it
 * 	      with a Color c and count x.
 *
 */
//! [0]
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
    MessageHandler * m_messagehandler;

    static const QString m_author; // for creating settings
    static const QString m_appName; // for creating settings

    // keys used in setting
    static const QString m_flashNumber;
    static const QString m_remainingCount;
    static const QString m_serviceStatus;
    static const QString m_ledActive;
    static const QString m_reset;
    // The Led instance
    bb::device::Led *m_led;
    // flash count holder
    int m_flashCount;
    // Watcher for qsettigns file changes
    QFileSystemWatcher* m_settingsWatcher;
};
//! [0]
#endif /* ApplicationHeadless_HPP_ */
