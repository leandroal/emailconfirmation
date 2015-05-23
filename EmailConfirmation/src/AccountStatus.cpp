/*
 * AccountStatus.cpp
 *
 *  Created on: 22/05/2015
 *      Author: dielson
 */

#include <src/AccountStatus.h>
#include <QSettings>
#include <QDebug>

AccountStatus::AccountStatus()
{
    QSettings settings("EmailConfirmation","listItem");
    m_settingsWatcherInfo.addPath(settings.fileName());
    bool ok = connect(&m_settingsWatcherInfo, SIGNAL(fileChanged(QString)), this, SLOT(refresh()));
    Q_ASSERT(ok);
}

AccountStatus::~AccountStatus()
{
}

QString AccountStatus::accountStatus() const {
    QSettings settings("EmailConfirmation","listItem");
    return settings.value("accountStatus", QString("No account")).toString();
}

void AccountStatus::refresh() {
    qDebug() << "Refreshing settings";
    emit statusChanged();
}
