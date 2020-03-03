import QtQuick 2.14
import QtQuick.Controls 2.14
import QtQuick.Controls.Material 2.14

import TaskModel 1.0


Pane {
    property var task

    Material.elevation: 6
    id: timerForm
    height: root.isMobile ? 110 : 50
//    height: 110

    TimerRowDesktop {
        visible: !root.isMobile
        task: timerForm.task
    }
    TimerRowMobile {
        id: mobileRow
        visible: root.isMobile

        task: timerForm.task
    }

    function formatTime(seconds) {
        if (seconds >= 60) {
            let minutes = Math.floor(seconds / 60)

            if (minutes >= 60) {
                return Math.floor(minutes / 60) + " h " + Math.floor(minutes % 60) + " min " + Math.floor(seconds % 60) + " sec"
            } else {
                return Math.floor(minutes) + " min " + Math.floor(seconds % 60) + " sec"
            }
        } else {
            return Math.floor(seconds) + " sec"
        }
    }
}
