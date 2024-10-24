import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Qt.labs.platform

ApplicationWindow {
    id: root
    width: 800
    height: 540
    visible: true
    title: qsTr("Maze")

    Connections {
        target: Controller
        function onMazeDataChanged() {
            console.log("Maze data changed");
            canvas.requestPaint(); // Запрашиваем перерисовку холста при изменении данных лабиринта
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

            property int rows: rowCountSpinBox.value
            property int cols: colCountSpinBox.value

            onPaint: {
                var ctx = getContext("2d");
                if (!ctx) {
                    console.log("Failed to get 2d context");
                    return;
                }
                ctx.fillStyle = "grey"; // Устанавливаем цвет заливки на серый
                ctx.fillRect(0, 0, width, height); // Заливаем весь холст серым цветом

                ctx.strokeStyle = "black";
                ctx.lineWidth = 2;
                var mazeData = Controller.getMazeData();
                console.log("Maze Data:", JSON.stringify(mazeData, null, 2));  // Добавьте это для отладки

                // Преобразуем одномерный массив в двумерный
                var mazeData2D = [];
                for (var i = 0; i < rows; i++) {
                    var row = [];
                    for (var j = 0; j < cols; j++) {
                        row.push(mazeData[i * cols + j]);
                    }
                    mazeData2D.push(row);
                }
                console.log("Maze Data 2D:", JSON.stringify(mazeData2D, null, 2));  // Добавьте это для отладки

                if (mazeData2D && mazeData2D.length > 0 && mazeData2D[0] && mazeData2D[0].length > 0) {
                    var cellSize = canvas.width / mazeData2D[0].length;
                    console.log("Cell size:", cellSize);
                    ctx.beginPath(); // Начинаем новый путь для всех стен

                    for (var i = 0; i < mazeData2D.length; i++) {
                        for (var j = 0; j < mazeData2D[i].length; j++) {
                            var cell = mazeData2D[i][j];
                            var x = j * cellSize;
                            var y = i * cellSize;
                            if (cell.r_wall) {
                                console.log("Drawing right wall at x:", x + cellSize, "y:", y);
                                ctx.moveTo(x + cellSize, y);
                                ctx.lineTo(x + cellSize, y + cellSize);
                            }
                            if (cell.b_wall) {
                                console.log("Drawing bottom wall at x:", x, "y:", y + cellSize);
                                ctx.moveTo(x, y + cellSize);
                                ctx.lineTo(x + cellSize, y + cellSize);
                            }
                        }
                    }
                    ctx.stroke(); // Завершаем путь и отрисовываем все стены
                } else {
                    console.log("Maze data is empty or invalid");
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
                    onClicked: {
                        Controller.saveMazeInFile();
                    }
                }

                Button {
                    id: loadButton
                    text: "Load"
                    font.pixelSize: 18
                    onClicked: {
                        fileDialog.open();
                    }
                }

                FileDialog {
                    id: fileDialog
                    title: "Choose a file with maze"
                    defaultSuffix: "txt"
                    nameFilters: ["Text files (*.txt)"]
                    onAccepted: {
                        //TODO преобразовать строку в std::string и передать её в функцию
                        var fileUrl = fileDialog.file.toString();
                        var filePath = fileUrl.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/, "");
                        var filePathString = filePath.toString();
                        console.log("File Path String:", filePathString);  // Добавьте это для отладки
                        Controller.loadMazeFromFile(filePathString);
                    }
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
                        Controller.mazeHeight = value;
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
                        Controller.mazeWidth = value;
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
                    Controller.generateMaze();
                    // Controller.printLabirinth();
                }
            }
        }
    }
}
