import QtQuick 2.12
import QtQuick.Window 2.2
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
    color: "#000000"
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
        id: coolanttemp
        width: 200
        height: 250
        anchors.leftMargin: parent.width /2 - width/2
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.topMargin: 0 - height/2.4
        maximumValue: 140
        minimumValue: -40
        value: Network.coolant
        style: CircularGaugeStyle{
            minorTickmarkCount: 1
            minimumValueAngle: -90
            maximumValueAngle: -270
            background: Image {
                id: image2
                x: 73
                width: 100
                height: 100
                anchors.top: parent.top
                anchors.topMargin: parent.height * .2
                anchors.horizontalCenter: parent.horizontalCenter
                source: "coolant.png"
                fillMode: Image.PreserveAspectFit
            }

        }


    }

    Text {
        id: maf
        width: 100
        height: 30
        color: "#ffffff"
        text: Network.airfuel.toFixed(2)+qsTr(" A/F")
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
        text: Network.tempature+qsTr(" °C")
        anchors.right: parent.right
        anchors.rightMargin: 190
        anchors.top: parent.top
        anchors.topMargin: 36
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: 27
    }

    Column {
        id: column
        x: 600
        y: 40
        width: parent.width *0.4
        height: parent.height * 0.7
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 0

        CircularGauge {
            id: rpm
            width: Math.min(parent.height, parent.width)
            height: Math.min(parent.height, parent.width)
            anchors.right: parent.right
            anchors.rightMargin: 0
            stepSize: 1
            maximumValue: 8000
            value: Network.rpm

            Behavior on value{
                NumberAnimation { duration: 1000 }
            }
            style: Rpmstyle {}

            Gauge {
                id: throttle
                x: 73
                y: 268
                width: parent.width * .5
                height: 40
                anchors.horizontalCenterOffset: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -50
                anchors.horizontalCenter: parent.horizontalCenter
                minimumValue: 0
                maximumValue: 100
                minorTickmarkCount: 1
                value: Network.throttle
                orientation: Qt.Horizontal

                Image {
                    id: image
                    x: 174
                    width: 45
                    height: 45
                    anchors.right: parent.right
                    anchors.rightMargin: -65
                    anchors.top: parent.verticalCenter
                    anchors.topMargin: -20
                    source: "qrc:/Throttle.PNG"
                    fillMode: Image.PreserveAspectFit
                }
            }

        }
    }

    Column {
        id: column1
        y: 72
        width: parent.width *0.4
        height: parent.height * 0.7
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 0

        CircularGauge {
            id: speed
            width: Math.min(parent.height, parent.width)
            height: Math.min(parent.height, parent.width)
            anchors.left: parent.left
            anchors.leftMargin: 0
            stepSize: 1
            value: Network.speed
            maximumValue: 180
            tickmarksVisible: true
            Behavior on value{
                NumberAnimation { duration: 1000 }
            }
            style: Speedstyle {}

            Gauge {
                id: voltage
                x: 78
                y: 337
                width: parent.width *.5
                height: 40
                anchors.horizontalCenterOffset: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: -50
                anchors.horizontalCenter: parent.horizontalCenter
                minimumValue: 10
                maximumValue: 16
                tickmarkStepSize: 1
                value: Network.voltage
                orientation: Qt.Horizontal

                Image {
                    id: image1
                    y: 337
                    width: 50
                    height: 40
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: -65
                    source: "qrc:/Voltage.PNG"
                    fillMode: Image.PreserveAspectFit
                }
            }
        }
    }






}































































/*##^## Designer {
    D{i:3;anchors_height:30;anchors_width:100;anchors_x:510;anchors_y:36}D{i:2;anchors_height:30;anchors_width:182;anchors_x:187;anchors_y:36}
D{i:1;anchors_height:30;anchors_width:100;anchors_x:296;anchors_y:36}D{i:4;anchors_height:30;anchors_width:100;anchors_x:10;anchors_y:36}
D{i:5;anchors_width:182;anchors_x:10;anchors_y:36}D{i:10;anchors_width:45;anchors_x:0;anchors_y:36}
D{i:9;anchors_height:30;anchors_width:45;anchors_x:296;anchors_y:36}D{i:8;anchors_height:30;anchors_width:100;anchors_x:510;anchors_y:36}
D{i:7;anchors_width:182;anchors_x:187;anchors_y:36}D{i:6;anchors_width:182;anchors_x:10;anchors_y:44}
D{i:15;anchors_height:40;anchors_x:"-59";anchors_y:337}D{i:14;anchors_height:40;anchors_width:800;anchors_x:"-59";anchors_y:337}
D{i:13;anchors_height:40;anchors_width:800;anchors_x:0;anchors_y:337}D{i:12;anchors_height:480;anchors_width:800;anchors_x:0;anchors_y:0}
D{i:11;anchors_height:480;anchors_width:800;anchors_x:0;anchors_y:0}
}
 ##^##*/
