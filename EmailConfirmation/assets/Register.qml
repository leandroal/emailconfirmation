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
                }
                Label {
                    text: qsTr("Email")
                }
                TextField {
                    id: emailField
                    hintText: qsTr("Type your email")
                    inputMode: TextFieldInputMode.EmailAddress
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