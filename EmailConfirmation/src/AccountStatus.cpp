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

#include <src/AccountStatus.h>
#include <QSettings>
#include <QTimer>
#include <QDebug>

QString AccountStatus::NO_ACCOUNT_MSG = QString("Click the \"Add account\" button to simulate a new account with automatic email confirmation");
QString AccountStatus::WAITING_CONFIRMATION_MSG = QString("Account [email] to be confirmed");
QString AccountStatus::CONFIRMED_MSG = QString("Account [email] confirmed");

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

QString AccountStatus::name() const {
    QSettings settings("EmailConfirmation","listItem");
    return settings.value("name", QString("")).toString();
}

QString AccountStatus::email() const {
    QSettings settings("EmailConfirmation","listItem");
    return settings.value("email", QString("")).toString();
}

void AccountStatus::saveForm(QString name, QString email) {
    QSettings settings("EmailConfirmation","listItem");
    settings.setValue("name", name);
    settings.setValue("email", email);
}

void AccountStatus::resetStatus() {
    QSettings settings("EmailConfirmation","listItem");
    settings.setValue("accountStatus", NO_ACCOUNT_MSG);
    settings.setValue("name", QString(""));
    settings.setValue("email", QString(""));
    emit confirmed();
}

QString AccountStatus::accountStatus() const {
    QSettings settings("EmailConfirmation","listItem");
    return settings.value("accountStatus", NO_ACCOUNT_MSG).toString();
}

void AccountStatus::refresh() {
    QSettings settings("EmailConfirmation","listItem");
    if (accountStatus() == CONFIRMED_MSG) {
        emit confirmed();
    }
    emit statusChanged();
}

void AccountStatus::onEmailSent() {
    QSettings settings("EmailConfirmation","listItem");
    settings.setValue("accountStatus", WAITING_CONFIRMATION_MSG);
    emit waitingConfirmation();
}
