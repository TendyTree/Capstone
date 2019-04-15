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


    /*TODO
      put styling of gauge in one file
      import contextproperty
      set gauges in more
      make them look better
      fix coolant temp
      */
    CircularGauge {
        id: speed
        x: 72
        anchors.verticalCenter: parent.verticalCenter
        width: parent.height * 0.7
        height: parent.height * 0.7
        stepSize: 1
        value: Network.speed
        maximumValue: 180
        anchors.left: parent.left
        anchors.leftMargin: parent.height * -0.3
        tickmarksVisible: true
        style: CircularGaugeStyle {
            id: speedstl
            minimumValueAngle: 185
            maximumValueAngle: 0
            tickmarkStepSize: 20
                foreground: Item {
                    Text {
                        id: speedLabels
                        anchors.centerIn: parent
                        text: Network.speed.toFixed(0)
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
    }


    CircularGauge {
        id: rpm
        x: -50
        y: 72
        anchors.verticalCenter: parent.verticalCenter
        width: parent.height * 0.7
        height: parent.height * 0.7
        stepSize: 1
        maximumValue: 8000
        value: Network.rpm
        anchors.rightMargin: parent.height * -0.3
        anchors.right: parent.right
        style: Rpmstyle {}

    }

    Gauge {
        id: voltage
        y: 419
        width: 182
        height: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 65
        minimumValue: 10
        maximumValue: 16
        tickmarkStepSize: 1
        value: Network.voltage
        orientation: Qt.Horizontal
    }
    Gauge {
        id: throttle
        x: 552
        y: 419
        width: 182
        height: 40
        anchors.right: parent.right
        anchors.rightMargin: 65
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        minimumValue: 0
        maximumValue: 100
        rotation: 180
        tickmarkAlignment: Qt.AlignTop
        value: Network.throttle
        orientation: Qt.Horizontal
        style: GaugeStyle {
            tickmarkLabel: Text {
                text: styleData.value
                rotation: 180
                color: "white"

            }

        }
    }

    CircularGauge {
        id: coolanttemp
        anchors.leftMargin: parent.width /2 - width/2
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 0 - height/2.4
        maximumValue: 140
        minimumValue: -40
        value: Network.coolant
        style: CircularGaugeStyle{
            minimumValueAngle: -90
            maximumValueAngle: -270

        }
    }

    Text {
        id: maf
        width: 100
        height: 30
        color: "#ffffff"
        text: Network.airfuel.toFixed(2)
        anchors.left: parent.left
        anchors.leftMargin: 187
        anchors.top: parent.top
        anchors.topMargin: 36
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 27
    }

    Text {
        id: airtemp
        x: 510
        width: 100
        height: 30
        color: "#ffffff"
        text: Network.tempature+qsTr("C")
        anchors.right: parent.right
        anchors.rightMargin: 190
        anchors.top: parent.top
        anchors.topMargin: 36
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 27
    }


}



































/*##^## Designer {
    D{i:1;anchors_height:480;anchors_width:800;anchors_x:0;anchors_y:0}D{i:7;anchors_x:10}
D{i:8;anchors_width:182;anchors_x:10}D{i:11;anchors_height:30;anchors_width:100;anchors_x:510;anchors_y:36}
D{i:10;anchors_x:187;anchors_y:36}D{i:9;anchors_width:182;anchors_y:44}D{i:13;anchors_height:30;anchors_width:100;anchors_x:510;anchors_y:36}
D{i:12;anchors_x:296;anchors_y:36}D{i:14;anchors_height:30;anchors_width:100;anchors_x:510;anchors_y:36}
D{i:15;anchors_height:30;anchors_width:100;anchors_x:510;anchors_y:36}
}
 ##^##*/
