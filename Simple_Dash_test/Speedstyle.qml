import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
CircularGaugeStyle {
    minimumValueAngle: 185
    maximumValueAngle: 0
    tickmarkStepSize: 20
    foreground: Item {
        Text {
            id: speedLabel
            anchors.centerIn: parent
            text: gauge.value.toFixed(0)
            Font.pixelSize: outerRadius * 0.3
            color: "white"
        }
    }
}

