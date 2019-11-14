import QtQuick 2.0
import QtQuick.Dialogs 1.2

Item{
    property string dbPath
    property bool hoover
    id: wrapper
    width: parent.width
    height: 25

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        onClicked:
        {
            wrapper.ListView.view.currentIndex = index
        }
        onEntered:
        {
            wrapper.hoover = true
        }
        onExited:
        {
            wrapper.hoover = false;
        }
        onDoubleClicked:
        {
            notImplementedDialog.open()
        }
    }

    Rectangle {
        id: delegateItem
        anchors.left: parent.left
        width: parent.width; height: parent.height
        color: "lightgray"

        Text {
            id: itexItem
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.verticalCenter: parent.verticalCenter
            text: dbPath
        }
    }

    states: [
        State {
            name: "Hoover"
            when: wrapper.hoover
            PropertyChanges { target: delegateItem; color: "lightslategrey" }
        },
        State {
            name: "Selected"
            when: wrapper.ListView.isCurrentItem
            PropertyChanges { target: delegateItem; color: "gray" }
        }
    ]

    // Dialogs
    MessageDialog { 
        id: notImplementedDialog
        title: "Warning"
        text: "Not implemented yet."
        icon: StandardIcon.Warning
    }
}
