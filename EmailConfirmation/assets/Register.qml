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

import bb.cascades 1.4

Sheet {
    id: mSheet
    Page {
        titleBar: TitleBar {
            title: qsTr("Adding Account")
            acceptAction: ActionItem {
                title: qsTr("Submit")
                onTriggered: {
                    _networkManager.submit(nameField.text, emailField.text, passwordField.text);
                    _status.saveForm(nameField.text, emailField.text);
                    mSheet.close();
                }
            }
            dismissAction: ActionItem {
                title: qsTr("Cancel")
                onTriggered: {
                    mSheet.close();
                }
            }
        }
        ScrollView {
            Container {
                topPadding: 20
                leftPadding: 20
                rightPadding: 20
                bottomPadding: 20
                Label {
                    text: qsTr("Nome")
                }
                TextField {
                    id: nameField
                    hintText: qsTr("Type your name")
                    onCreationCompleted: {
                        nameField.setText(_status.name());
                    }
                }
                Label {
                    text: qsTr("Email")
                }
                TextField {
                    id: emailField
                    hintText: qsTr("Type your email")
                    inputMode: TextFieldInputMode.EmailAddress
                    onCreationCompleted: {
                        emailField.setText(_status.email());
                    }
                }
                Label {
                    text: qsTr("Password")
                }
                TextField {
                    id: passwordField
                    hintText: qsTr("Type your password")
                    inputMode: TextFieldInputMode.Password
                }
            }
        }
        
    }
}