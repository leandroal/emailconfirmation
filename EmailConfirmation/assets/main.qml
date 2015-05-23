import bb.cascades 1.4

Page {
    attachedObjects: [
        SettingsPage {
            id:settingsPage
        },
        ComponentDefinition {
            id: mRegisterFactory
            Register {
            }
        }
    ]
    titleBar: TitleBar {
        title: "Account Status"
        acceptAction: ActionItem {
            imageSource: "asset:///images/ic_settings.png"
            onTriggered: {
                settingsPage.open()
            }
        }
    }
    actions: [
        ActionItem {
            title: "Add Account"
            imageSource: "asset:///images/ic_add.png"
            ActionBar.placement: ActionBarPlacement.OnBar
            onTriggered: {
                var registerObject = mRegisterFactory.createObject();
                registerObject.open();
            }
        }
    ]
    Container {
        layout: DockLayout {
            
        }
        Container {
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            Label {
                text: _status.statusMessage
                textFit.minFontSizeValue: 11.0

            }
        }
    }
}
