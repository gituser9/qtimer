import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14
import QtQuick.Layouts 1.14
import Qt.labs.settings 1.1
import Qt.labs.platform 1.0

import TaskModel 1.0


ApplicationWindow {
    id: root
    visible: true
    height: 480
    width: 640
    title: qsTr("Qtimer")

    property bool isMobile: Qt.platform.os == "android" || Qt.platform.os == "ios"
    property var tasks: []
    property TaskModel taskModel: TaskModel{}


    ScrollView {
        anchors.fill: parent


        ListView {
            id: listView
            width: parent.width
            model: taskModel
            spacing: 10
            delegate: TimerItem {
                width: parent.width - 20
                anchors.horizontalCenter: parent.horizontalCenter
                task: model
            }
            remove: Transition {
                ParallelAnimation {
                    NumberAnimation { property: "opacity"; to: 0; duration: 300 }
                }
            }
            add: Transition {
                NumberAnimation { property: "opacity"; to: 100; duration: 800 }
            }
        }
    }

    RoundButton {
        id: addButton
        width: 60
        height: 60
        y: parent.height - height - 12
        anchors.right: parent.right
        anchors.margins: 12
        highlighted: true

        onClicked: {
            taskModel.create()
        }
        contentItem: Image {
            horizontalAlignment: Image.AlignHCenter
            verticalAlignment: Image.AlignVCenter
            source: "qrc:/image/add_white.png"
            scale: 0.7
        }
    }

//    Settings {
//        id: taskSettings
//        property var taskList: tasks
//    }

    SystemTrayIcon {
        id: trayIcon
        visible: !isMobile
        iconSource: "qrc:/image/timer_white.png"
        onActivated: {
            if (reason === SystemTrayIcon.Trigger) {
                if (root.visible) {
                    root.hide()
                } else {
                    root.show()
                }
            }
        }
        menu: Menu {
            MenuItem {
                text: qsTr("Quit")
                onTriggered: Qt.quit()
            }
        }
    }

}
