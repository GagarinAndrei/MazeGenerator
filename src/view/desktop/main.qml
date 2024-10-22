import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: root
    width: 800
    height: 540
    visible: true
    title: qsTr("Maze")

    Connections {
        target: Controller
        function onMazeDataChanged() {
            canvas.requestPaint(
                        ) // Запрашиваем перерисовку холста при изменении данных лабиринта
        }
    }

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
                var ctx = getContext("2d")

                ctx.fillStyle = "grey" // Устанавливаем цвет заливки на серый
                ctx.fillRect(0, 0, width,
                             height) // Заливаем весь холст серым цветом

                context.strokeStyle = "#22a6b3"
                context.lineWidth = 2
                var mazeData = Controller.mazeData
                if (mazeData && mazeData.length > 0) {
                    var cellSize = width / mazeData[0].length
                    for (var i = 0; i < mazeData.length; i++) {
                        for (var j = 0; j < mazeData[i].length; j++) {
                            var cell = mazeData[i][j]
                            var x = j * cellSize
                            var y = i * cellSize
                            if (cell.r_wall) {
                                ctx.beginPath()
                                ctx.moveTo(x + cellSize, y)
                                ctx.lineTo(x + cellSize, y + cellSize)
                                ctx.stroke()
                            }
                            if (cell.b_wall) {
                                ctx.beginPath()
                                ctx.moveTo(x, y + cellSize)
                                ctx.lineTo(x + cellSize, y + cellSize)
                                ctx.stroke()
                            }
                        }
                    }
                }
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
                    onValueChanged: {
                        Controller.mazeHeight = value
                    }
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
                    onValueChanged: {
                        Controller.mazeWidth = value
                    }
                }
            }

            Button {
                id: generateButton
                text: "Generate"
                font.pixelSize: 18
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                onClicked: {
                    Controller.generateMaze()
                    Controller.printLabirinth()
                }
            }
        }
    }
}
