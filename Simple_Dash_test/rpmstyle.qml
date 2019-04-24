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
    tickmark: Rectangle {
        visible: styleData.value < 80 || styleData.value % 10 == 0
        implicitWidth: outerRadius * 0.02
        antialiasing: true
        implicitHeight: outerRadius * 0.08
        color: styleData.value >= 7000 ? "#e34c22" : "#e5e5e5"
        }

    minorTickmark: Rectangle {
        implicitWidth: outerRadius * 0.01
        antialiasing: true
        implicitHeight: outerRadius * 0.03
        color: styleData.value >= 7000 ? "#e34c22" : "#e5e5e5"
        }

    tickmarkLabel:  Text {
        font.pixelSize: Math.max(6, outerRadius * 0.1)
        text: styleData.value
        color: styleData.value >= 7000 ? "#e34c22" : "#e5e5e5"
        antialiasing: true
        }
}

