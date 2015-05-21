import bb.cascades 1.4
Sheet {
    id: sheetPage

Page {
    
    titleBar: TitleBar {
        title: "Settings"
        dismissAction: ActionItem {
            title: "Back"
            onTriggered: {
                sheetPage.close()
            }
        }
    }
    Container {
        Label {
            text: "Address Emails Accepted"
        }
        
        
    
    Container {
        
      
//        ListView {
//            rightPadding: 50
//            leftPadding: 50
//            
//            onCreationCompleted: {
//                model.append({ "Address": "Facebook" })
//            }
//            dataModel: model
//            listItemComponents:[
//                ListItemComponent {
//                    StandardListItem {
//                        title: ListItemData.Address
//                    }
//                }
//            ]
//        }
        DropDown {
            onCreationCompleted: {
                
            }
            id: accounts
            title: "Account"
            enabled: true
            onOptionAdded: {
                if(option.text == ""){
                    option.text = "no name"
                }
            }
       
     
        }
        
    }
}
    attachedObjects: [
        ArrayDataModel {
            id:model
        },
        RenderFence {
            raised: true
            onReached: {
                _appUI.addElementsDropDown(accounts)
            }
        }
    ]
}
}
