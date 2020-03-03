import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14


Item {
    property var task
    property int seconds: 0

    id: mobileItem
    anchors.fill: parent

    Timer {
        id: taskTimer
        interval: 1000;
        running: false;
        repeat: true
        onTriggered: {
            value.text = timerForm.formatTime(++seconds)
            task.seconds = seconds
            root.updateTask(task, seconds)
        }
    }

    Column {
        anchors.fill: parent

        Row {
            id: row
            width: parent.width

            TextField {
                id: name
                width: parent.width
                text: task.name
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 14
                onEditingFinished: {
                    task.name = text
                    root.updateTask(task, seconds)
                }
                leftPadding: 10
            }
        }
        Row {
            id: toolButtonRow
            width: parent.width

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
                onClicked: taskTimer.stop()
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
                    root.updateTask(task, seconds)
                    value.text = qsTr("0 sec")
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
                    root.deleteTask(task)
                }
            }
            Text {
                id: value
                text: timerForm.formatTime(task.seconds)
                anchors.verticalCenter: parent.verticalCenter
//                anchors.right: toolButtonRow.right
                font.pixelSize: 18
            }
        }
    }
}



