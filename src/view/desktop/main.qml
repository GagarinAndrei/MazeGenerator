import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: 800
    height: 540
    visible: true
    title: qsTr("Maze")
    
    RowLayout {
        id: row
        spacing: 12
        anchors.margins: 16
        anchors.fill: parent

        Canvas {
            id: canvas
            width: 500
            height: 500
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            onPaint: {
                var ctx = getContext("2d");
                ctx.fillStyle = "grey";  // Устанавливаем цвет заливки на зеленый
                ctx.fillRect(0, 0, width, height);  // Заливаем весь холст зеленым цветом
            }
        }

        ColumnLayout {
            spacing: 12
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            RowLayout {
                id: buttonRow
                spacing: 12
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

                Button {
                    id: saveButton
                    text: "Save"
                    font.pixelSize: 18
                }
                Button {
                    id: loadButton
                    text: "Load"
                    font.pixelSize: 18
                }
            }

            Text {
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                text: "Generation settings:"
            }

            RowLayout {
                Text {
                    text: "Maze rows:"
                    Layout.preferredWidth: 80
                }
                SpinBox {
                    id: rowCountSpinBox
                    Layout.alignment: Qt.AlignRight
                    Layout.fillWidth: true
                    from: 0
                    to: 50
                }
            }

            RowLayout {
                Text {
                    text: "Maze cols:"
                    Layout.preferredWidth: 80
                }
                SpinBox {
                    id: colCountSpinBox
                    Layout.alignment: Qt.AlignRight
                    Layout.fillWidth: true
                    from: 0
                    to: 50
                }
            }

            Button {
                id: generateButton
                text: "Generate"
                font.pixelSize: 18
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
            }
        }
    }
}
