import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.13

import Ht.RecentDatabasesModel 1.0

Page{
    horizontalPadding: 10
    id: welcomePage
    padding: 20

    header: Text {
        text: qsTr("Welcome to HT")
        font.pointSize: 20
        height: 20
        x: 10
    }

    Text {
        y: 20
        x: 20
        id: recentDbText
        text: qsTr("Open recent")
        // anchors.horizontalCenter: parent.horizontalCenter
    }

    ListView {
        id: recentDatabases
        anchors.top: recentDbText.bottom

        width: parent.width
        model: RecentDatabasesModel {}
        height: count * 25 + 10

        delegate: RecentDatabasesDelegate{
            dbPath: model.display
        }
    }

    RowLayout
    {
        id: buttonsLayout
        anchors.top: recentDatabases.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 6
        
        Button {
            id: createButton
            text: "Create"
            Layout.preferredHeight: 25
            onClicked: {
                notImplementedDialog.open()
            }
        }
        Button {
            id: browseButton
            text: "Browse"
            Layout.preferredHeight: 25
            onClicked: {
                notImplementedDialog.open()
            }
        }
        Button {
            id: openButton
            text: "Open"
            Layout.preferredHeight: 25
            onClicked: {
                notImplementedDialog.open()
            }
        }
    }

    // Dialogs
    MessageDialog { 
        id: notImplementedDialog
        title: "Warning"
        text: "Not implemented yet."
        icon: StandardIcon.Warning
    }

    FileDialog {
        id: fileDialog
        selectMultiple: false
        selectFolder: false
        nameFilters: ["Database files (*.db)", "Any file (*)"]
        onAccepted:{
            console.log(this.fileUrl)
            selectDbField.text = this.fileUrl
        }
    }
}

