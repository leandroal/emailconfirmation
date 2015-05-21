import bb.cascades 1.4

Sheet {
    id: mSheet
    Page {
        titleBar: TitleBar {
            title: qsTr("Adding Account")
            acceptAction: ActionItem {
                title: qsTr("Submit")
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
                    text: qsTr("Email")
                }
                TextField {
                    hintText: qsTr("Type your email")
                    inputMode: TextFieldInputMode.EmailAddress
                }
                Label {
                    text: qsTr("Password")
                }
                TextField {
                    hintText: qsTr("Type your password")
                    inputMode: TextFieldInputMode.Password
                }
            }
        }
        
    }
}