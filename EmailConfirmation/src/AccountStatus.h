/*
 * AccountStatus.h
 *
 *  Created on: 22/05/2015
 *      Author: dielson
 */

#ifndef ACCOUNTSTATUS_H_
#define ACCOUNTSTATUS_H_

#include <QFileSystemWatcher>

class AccountStatus: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString statusMessage READ accountStatus NOTIFY statusChanged)
public:
    AccountStatus();
    virtual ~AccountStatus();
    Q_INVOKABLE QString accountStatus() const;
signals:
    void statusChanged();
public slots:
    void refresh();
private:
    QFileSystemWatcher m_settingsWatcherInfo;
};

#endif /* ACCOUNTSTATUS_H_ */
