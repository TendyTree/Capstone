import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
CircularGaugeStyle {
    minimumValueAngle: -185
    maximumValueAngle: 0
    tickmarkStepSize: 1000
    foreground: Item {
        Text {
            id: rpmlabel
            anchors.centerIn: parent
            text: rpm.value.toFixed(0)
            font.pixelSize: outerRadius * 0.3
            color: "white"
            antialiasing: true
        }
    }
    needle: Rectangle {
        y: outerRadius * -.15
        implicitWidth: outerRadius * 0.03
        implicitHeight: outerRadius * 0.9
        antialiasing: true
        color: "red"
    }
}

