import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 641
    height: 480
    title: qsTr("Hello World")

    StackView {
        anchors.fill: parent
        id: pages

        initialItem: WelcomePage{}
    }

}
