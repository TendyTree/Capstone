import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
Defaultgauge{
    minimumValueAngle: -140
    maximumValueAngle: 140
    tickmarkStepSize: 20
        foreground: Item {
            Rectangle {
                width: outerRadius
                height: width
                radius: width / 2
                color: "black"
                anchors.centerIn: parent
            }
            Text {
                id: speedLabels
                anchors.centerIn: parent
                text: Network.speed.toFixed(0)
                font.pixelSize: outerRadius * 0.3
                color: "white"
                antialiasing: true
            }
            Text {
                text: "km/h"
                color: "white"
                font.pixelSize: 12
                anchors.top: speedLabels.bottom
                anchors.horizontalCenter: parent.horizontalCenter
            }

        }


}

