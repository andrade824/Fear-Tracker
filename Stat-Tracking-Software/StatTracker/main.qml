import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import DataStorage 1.0

ApplicationWindow {
    title: qsTr("Hello World")
    width: 1000
    height: 800
    visible: true

    menuBar: MenuBar {
        Menu {
            title: qsTr("&File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: messageDialog.show(qsTr("Open action triggered"));
            }
            MenuItem {
                text: qsTr("E&xit")
                onTriggered: Qt.quit();
            }
        }
    }

    MainForm {
        anchors.fill: parent
        button1.onClicked: messageDialog.show(qsTr("Button 1 pressed"))
        button2.onClicked: messageDialog.show(qsTr("Button 2 pressed"))
        button3.onClicked: messageDialog.show(qsTr("Button 3 pressed"))

        Timer {
             interval: 500;
             running: true;
             repeat: true
             onTriggered: {
                 TestData.addGarbage();
             }
         }

        Graph {
            id: graph1
            type: FearDataNode.TYPE_HEART
            minY: 60
            maxY: 120
            z: -1
            height: 200
            width: parent.width
            y: 0
            x: 0
        }

        Graph {
            id: graph2
            type: FearDataNode.TYPE_SWEAT
            minY: 0
            maxY: 100
            z: -1
            height: 200
            width: parent.width
            y: 200
            x: 0
        }

        Graph {
            id: graph3
            type: FearDataNode.TYPE_FEAR
            minY: 0
            maxY: 100
            z: -1
            height: 200
            width: parent.width
            y: 400
            x: 0
        }

        Graph {
            id: graph4
            type: FearDataNode.TYPE_JUMP
            minY: 0
            maxY: 1
            z: -1
            height: 200
            width: parent.width
            y: 600
            x: 0
        }
    }

    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
