import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12

import Ht.RecentDatabasesModel 1.0

Page{
    id: welcomePage
    header: Text {
        text: qsTr("\tWelcome to HT")
        height: 20
    }
    Text {
        x: 10
        y: 20
        id: selectDbText
        text: qsTr("Please enter path to database file")
    }
    TextField {
        id: selectDbField
        anchors.top: selectDbText.bottom
        anchors.left: selectDbText.left
        placeholderText: qsTr("Enter path to database file")
        width: 400
        height: 30
        anchors.leftMargin: 0
        anchors.topMargin: 0
    }
    Button {
        id: selectDbButton
        anchors.left: selectDbField.right
        anchors.top: selectDbField.top
        text: "Browse"
        height: selectDbField.height
        onClicked: {
            fileDialog.open()
        }
    }
    Button {
        id: connectToDbButton
        anchors.left: selectDbButton.right
        anchors.top: selectDbButton.top
        text: "Open"
        height: selectDbButton.height
        onClicked: {
            notImplementedDialog.open()
        }
    }

    Text {
        x: 10
        y: 80
        id: recentDbText
        text: qsTr("Or select from recent files")
    }

    ListView {
        id: recentDatabases
        anchors.top: recentDbText.bottom
        anchors.left: recentDbText.left
        width: 400
        model: RecentDatabasesModel {}
        height: 100

        delegate: RecentDatabasesDelegate{
            dbPath: model.display
        }
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

    MessageDialog {
        id: notImplementedDialog
        title: "Warning"
        text: "Not implemented yet."
        icon: StandardIcon.Warning
    }
}

