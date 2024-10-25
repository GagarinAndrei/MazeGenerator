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
        target: View
        function onMazeDataChanged() {
            // console.log("Maze data changed");
            canvas.requestPaint();
        }
    }

    RowLayout {
        id: rowLayaut
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
                ctx.fillStyle = "grey";
                ctx.fillRect(0, 0, width, height);
                ctx.strokeStyle = "black";
                ctx.lineWidth = 2;
                var mazeData = View.getMazeData();
                console.log("Maze Data:", JSON.stringify(mazeData, null, 2));  // Добавьте это для отладки
                // console.log("Maze Hight:", View.getHight);  // Добавьте это для отладки
                // console.log("Maze Width:", mazeWidth);  // Добавьте это для отладки

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
                    var devider = (mazeData2D.length > mazeData2D[0].length) ? mazeData2D.length : mazeData2D[0].length;
                    var cellSize = canvas.width / devider;
                    // console.log("Devider size:", devider);
                    // console.log("Cell size:", cellSize);
                    ctx.beginPath();
                    for (var i = 0; i < mazeData2D.length; i++) {
                        for (var j = 0; j < mazeData2D[i].length; j++) {
                            var cell = mazeData2D[i][j];
                            var x = j * cellSize;
                            var y = i * cellSize;
                            if (cell.r_wall) {
                                ctx.moveTo(x + cellSize, y);
                                ctx.lineTo(x + cellSize, y + cellSize);
                            }
                            if (cell.b_wall) {
                                ctx.moveTo(x, y + cellSize);
                                ctx.lineTo(x + cellSize, y + cellSize);
                            }
                        }
                    }
                    ctx.stroke();
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
                        saveFile.open();
                    }
                }

                FileDialog {
                    id: saveFile
                    title: "Save maze in file"
                    fileMode: FileDialog.SaveFile
                    nameFilters: ["Text files (*.txt)"]
                    onAccepted: {
                        var filePath = saveFile.file.toString();
                        if (filePath.startsWith("file://")) {
                            filePath = filePath.substring(7);
                        }
                        View.saveMazeInFile(filePath);
                    }
                }

                Button {
                    id: loadButton
                    text: "Load"
                    font.pixelSize: 18
                    onClicked: {
                        loadFile.open();
                    }
                }

                FileDialog {
                    id: loadFile
                    title: "Choose a file with maze"
                    fileMode: FileDialog.OpenFile
                    defaultSuffix: "txt"
                    nameFilters: ["Text files (*.txt)"]
                    onAccepted: {
                        //TODO преобразовать строку в std::string и передать её в функцию
                        var fileUrl = loadFile.file.toString();
                        var filePath = fileUrl.replace(/^(file:\/{2})|(qrc:\/{2})|(http:\/{2})/, "");
                        var filePathString = filePath.toString();
                        console.log("File Url:", fileUrl);  // Добавьте это для отладки
                        console.log("File Path String:", filePathString);  // Добавьте это для отладки
                        View.loadMazeFromFile(filePathString);
                        rowCountSpinBox.value = View.printLabirinth();
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
                        View.mazeHeight = value;
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
                        View.mazeWidth = value;
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
                    View.generateMaze();
                    View.printLabirinth();
                }
            }
        }
    }
}
