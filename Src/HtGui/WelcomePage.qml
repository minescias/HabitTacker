import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.13
import QtQuick.Controls.Styles 1.4

import Ht.RecentDatabasesModel 1.0
import "./Components"

Page{
    horizontalPadding: 10
    id: welcomePage
    padding: 20

    header: Text {
        text: qsTr("Welcome to HT :)")
        font.pointSize: 20
        height: 20
        x: 10
    }

    Text {
        y: 20
        x: 20
        id: recentDbText
        text: qsTr("Open recent")
    }

    ListView {
        id: recentDatabases
        anchors.top: recentDbText.bottom
        width: parent.width
        model: RecentDatabasesModel {}
        spacing: 1
        height: count * 26 + 10
        interactive: false

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

        HtButton{
            id: createButton
            text: "Create"
            Layout.preferredHeight: height
            Layout.preferredWidth: width
            onClicked: {
                notImplementedDialog.open()
            }
        }

        HtButton{
            id: browseButton
            text: "Browse"
            Layout.preferredHeight: height
            Layout.preferredWidth: width
            onClicked: {
                notImplementedDialog.open()
            }
        }

        HtButton{
            id: openButton
            text: "Open"
            Layout.preferredHeight: height
            Layout.preferredWidth: width
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

    // might be useful for debugging
    // Timer {
    //     interval: 500; running: true; repeat: true
    //     onTriggered: console.log(browseButton.hovered)
    // }
}

