import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2
import QtQuick.Shapes 1.0
import QtQuick.Extras 1.4
import QtQuick.Controls.Styles 1.4
Window {
    id: window
    visible: true
    minimumHeight : 200
    minimumWidth : 200
    width: 800
    height: 480
    color: "#201f1f"
    opacity: 1
    title: qsTr("Dash Test")

    CircularGauge {
        id: speed
        x: 72
        anchors.verticalCenter: parent.verticalCenter
        width: parent.height * 0.7
        height: parent.height * 0.7
        value: 50.5
        anchors.left: parent.left
        anchors.leftMargin: parent.height * -0.3

    }

    CircularGauge {
        id: rpm
        x: -50
        y: 72
        anchors.verticalCenter: parent.verticalCenter
        width: parent.height * 0.7
        height: parent.height * 0.7
        anchors.rightMargin: parent.height * -0.3
        anchors.right: parent.right
        CircularGauge {
               id: gauge
               anchors.fill: parent
               style: CircularGaugeStyle {
                   labelInset: outerRadius * 0.2

                   tickmarkLabel: null

                   tickmark: Text {
                       text: styleData.value

                       Text {
                           anchors.horizontalCenter: parent.horizontalCenter
                           anchors.top: parent.bottom
                           text: styleData.index
                           color: "blue"
                       }
                   }

                   minorTickmark: Text {
                       text: styleData.value
                       font.pixelSize: 8

                       Text {
                           anchors.horizontalCenter: parent.horizontalCenter
                           anchors.top: parent.bottom
                           text: styleData.index
                           font.pixelSize: 8
                           color: "blue"
                       }
                   }
               }

               Text {
                   id: indexText
                   text: "Major and minor indices"
                   anchors.horizontalCenter: parent.horizontalCenter
                   anchors.bottom: valueText.top
                   color: "blue"
               }
               Text {
                   id: valueText
                   text: "Major and minor values"
                   anchors.horizontalCenter: parent.horizontalCenter
                   anchors.bottom: parent.bottom
               }
        }

    }

    Gauge {
        id: gauge1
        x: 79
        y: 346
        value: 50
        rotation: 90
    }

    Text {
        id: element
        x: 323
        y: 166
        text: qsTr("Text")
        font.family: "Courier"
        font.pixelSize: 12
    }


}













/*##^## Designer {
    D{i:1;anchors_height:480;anchors_width:800;anchors_x:0;anchors_y:0}
}
 ##^##*/
