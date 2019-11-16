import QtQuick 2.0
import QtQuick.Controls 2.12
// import QtQuick.Layouts 1.13
// import QtQuick.Dialogs 1.2


Button {
    id: openButton
    width: 100
    height: 25
    hoverEnabled: true

    background: Rectangle {
        id: backRec2
        color: "lightgrey"
    }
    states: [
        State {
            name: "Pressed"
            when: openButton.pressed
            PropertyChanges { target: backRec2; color: "grey"}
        },
        State {
            name: "Hover"
            when: openButton.hovered
            PropertyChanges { target: backRec2; color: "lightsteelblue"}
        }
    ]
}