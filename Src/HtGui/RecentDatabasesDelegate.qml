import QtQuick 2.0

Item{
    property string dbPath
    id: wrapper
    width: parent.width
    height: 25

    MouseArea {
        anchors.fill: parent
        onClicked:
        {
            console.error("log completed")
            wrapper.ListView.view.currentIndex = index
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

    states: State {
        name: "Current"
        when: wrapper.ListView.isCurrentItem
         PropertyChanges { target: delegateItem; color: "gray" }
    }
}
