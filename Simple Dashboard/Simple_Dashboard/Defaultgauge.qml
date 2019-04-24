
import QtQuick 2.2
import QtQuick.Controls.Styles 1.4

CircularGaugeStyle{

    background: Item{
        Rectangle {
                width: outerRadius*2
                height: width
                radius: width
                color: "#161616"
                anchors.centerIn: parent
            }
        Canvas {
                        property int value: control.value
                        anchors.fill: parent
                        onValueChanged: requestPaint()
                        function degreesToRadians(degrees) {
                          return degrees * (Math.PI / 180);
                        }

                        onPaint: {
                            var ctx = getContext("2d");
                            ctx.reset();
                            ctx.beginPath();
                            ctx.strokeStyle = "red"
                            ctx.lineWidth = outerRadius * 0.05;
                            ctx.arc(outerRadius,
                                  outerRadius,
                                  outerRadius - ctx.lineWidth / 2,
                                  degreesToRadians(valueToAngle(control.minimumValue)-90),
                                  degreesToRadians(valueToAngle(control.value)-90));
                            ctx.stroke();
                        }
        }
    }
    needle: Rectangle {
                    y: outerRadius * -.1
                    implicitWidth: outerRadius * 0.03
                    implicitHeight: outerRadius * .9
                    antialiasing: true
                    color: "red"
                }

}
