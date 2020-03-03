import QtQuick 2.14
import QtQuick.Controls 2.14


Item {
    property var task
    property int seconds: 0

    anchors.fill: parent

    Component.onCompleted: {
        seconds = task.seconds
    }
    Component.onDestruction: {
        root.taskModel.update(task.id, seconds, task.name)
    }

    Row {
        id: row
        anchors.fill: parent
        spacing: 10
        leftPadding: 10

        Timer {
            id: taskTimer
            interval: 1000
            running: false
            repeat: true
            onTriggered: {
                value.text = timerForm.formatTime(++seconds)
                task.seconds = seconds
            }
        }

        TextField {
            id: name
            width: parent.width / 3
            text: task.name
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 14
            onEditingFinished: {
                root.taskModel.update(task.id, task.seconds, name.text)
            }
            leftPadding: 10
        }
        Text {
            id: value
            text: formatTime(task.seconds)
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 14
            width: 100
        }
        ToolButton {
            id: startButton
            implicitHeight: 50
            implicitWidth: 50
            anchors.verticalCenter: parent.verticalCenter
            contentItem: Image {
                source: "qrc:/image/start.png"
                scale: 0.6
            }
            onClicked: {
                taskTimer.start()
            }
        }
        ToolButton {
            id: stopButton
            implicitHeight: 50
            implicitWidth: 50
            anchors.verticalCenter: parent.verticalCenter
            contentItem: Image {
                source: "qrc:/image/pause.png"
                scale: 0.6
            }
            onClicked: {
                taskTimer.stop()
                root.taskModel.update(task.id, seconds, name.text)
            }
        }
        ToolButton {
            id: resetButton
            implicitHeight: 50
            implicitWidth: 50
            anchors.verticalCenter: parent.verticalCenter
            contentItem: Image {
                source: "qrc:/image/stop.png"
                scale: 0.6
            }
            onClicked: {
                taskTimer.stop()
                task.seconds = 0
                seconds = 0
//                root.updateTask(task, seconds)
                value.text = qsTr("0 sec")
                root.taskModel.update(task.id, 0, name.text)
            }
        }
        ToolButton {
            id: deleteButton
            implicitHeight: 50
            implicitWidth: 50
            anchors.verticalCenter: parent.verticalCenter
            contentItem: Image {
                source: "qrc:/image/delete.png"
                scale: 0.6
            }
            onClicked: {
                root.taskModel.remove(task.id)
            }
        }
    }

}

