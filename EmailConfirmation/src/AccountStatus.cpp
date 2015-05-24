/* E-mail confirmation sample for BlackBerry 10 - Client side
 * Copyright (C) <2015> Dielson Carvalho <dielson.carvalho@compelab.org>
 * Copyright (C) <2015> Durval Pereira <durval@compelab.org>
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

void AccountStatus::onEmailSent() {
    QSettings settings("EmailConfirmation","listItem");
    settings.setValue("accountStatus", QString("To be confirmed"));
}
