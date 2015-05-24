/* E-mail confirmation sample for BlackBerry 10 - Client side
 * Copyright (C) <2015> Dielson Carvalho <dielson.carvalho@compelab.org>
 * Copyright (C) <2015> Leandro Melo de Sales <leandro@compelab.org>
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU. Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this code; if not, write to the


 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef ACCOUNTSTATUS_H_
#define ACCOUNTSTATUS_H_

#include <QFileSystemWatcher>

class AccountStatus: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString statusMessage READ accountStatus NOTIFY statusChanged)
public:
    static QString WAITING_CONFIRMATION_MSG;
    static QString NO_ACCOUNT_MSG;
    static QString CONFIRMED_MSG;
    AccountStatus();
    virtual ~AccountStatus();
    Q_INVOKABLE void resetStatus();
    Q_INVOKABLE QString accountStatus() const;
    Q_INVOKABLE void saveForm(QString name, QString email);
    Q_INVOKABLE QString name() const;
    Q_INVOKABLE QString email() const;
signals:
    void statusChanged();
    void waitingConfirmation();
    void confirmed();
public slots:
    void onEmailSent();
    void refresh();
private:
    QFileSystemWatcher m_settingsWatcherInfo;
};

#endif /* ACCOUNTSTATUS_H_ */
