import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
Defaultgauge {
    id: rpmstyling
    minimumValueAngle: -140
    maximumValueAngle: 140
    tickmarkStepSize: 1000
    foreground: Item {
        Rectangle {
            width: outerRadius
            height: width
            radius: width / 2
            color: "black"
            anchors.centerIn: parent
        }
        Text {
            id: rpmlabel
            anchors.centerIn: parent
            text: rpm.value.toFixed(0)
            font.pixelSize: outerRadius * 0.3
            color: "white"
            antialiasing: true
        }
        Text {
            text: "RPM"
            color: "white"
            font.pixelSize: 12
            anchors.top: rpmlabel.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }
}

