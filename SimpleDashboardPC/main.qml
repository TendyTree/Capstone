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
            tickmarkStepSize: 20
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

    Image {
        id: image3
        x: 288
        y: 209
        width: 200
        height: 200
        anchors.bottom: parent.bottom
        anchors.bottomMargin: -30
        anchors.horizontalCenter: parent.horizontalCenter
        fillMode: Image.PreserveAspectFit
        source: "qrc:/Tempature.png"

        Text {
            id: airtemp
            x: 18
            y: 94
            width: 182
            height: 30
            color: "#020202"
            text: Network.tempature+qsTr(" °c")
            anchors.horizontalCenter: parent.horizontalCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 27
        }
    }


    Column {
        id: leftcol
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
            maximumValue: 180
            tickmarksVisible: true
            value: Network.speed
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


    Column {
        id: rightcol
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
                minorTickmarkCount: 3
                tickmarkStepSize: 20
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

}

