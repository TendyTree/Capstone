import QtQuick 2.12
import QtQuick.Window 2.2
import QtQuick.VirtualKeyboard 2.2
import QtQuick.Shapes 1.0

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


    Shape {
        id: shape
        x: 0
        y: 0
        width: window.width
        height: window.height
        antialiasing: true
        transformOrigin: Item.TopLeft
        scale: 1

        Text {
            id: element
            x: 36
            y: 215
            width: 160
            height: 45
            color: "#ffffff"
            text: qsTr("180 MPH")
            styleColor: "#ffffff"
            horizontalAlignment: Text.AlignRight
            anchors.left: parent.left
            anchors.leftMargin: 36
            anchors.top: parent.top
            anchors.topMargin: 215
            font.family: "Arial"
            transformOrigin: Item.TopLeft
            font.pixelSize: 38
        }

        ShapePath {
            fillColor: "transparent"
            strokeColor: "darkBlue"
            strokeWidth: 20
            capStyle: ShapePath.FlatCap

            PathAngleArc {
                centerX: 0; centerY: window.height/2
                radiusX: Math.min(window.height, window.width)/2 - 10; radiusY:Math.min(window.height, window.width)/2 - 10;
                startAngle: 90
                sweepAngle: -150

            }
        }

    }
}









/*##^## Designer {
    D{i:4;anchors_height:45;anchors_width:160;anchors_x:36;anchors_y:215}
}
 ##^##*/
