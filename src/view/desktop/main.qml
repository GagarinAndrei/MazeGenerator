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
            canvas.requestPaint();
        }
    }

    RowLayout {
        id: rowLayout
        spacing: 12
        anchors.margins: 16
        anchors.fill: parent

        Canvas {
            id: canvas
            width: 500
            height: 500
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            property int rows: rowsSpinBox.value
            property int cols: colsSpinBox.value
            property var startPoint: null
            property var endPoint: null

            onPaint: {
                var ctx = getContext("2d");
                if (!ctx) return;

                ctx.fillStyle = "grey";
                ctx.fillRect(0, 0, width, height);
                ctx.clearRect(0, 0, width, height);
                ctx.strokeStyle = "black";
                ctx.lineWidth = 2;

                var mazeData = View.getMazeData();
                rows = rowsSpinBox.value;
                cols = colsSpinBox.value;

                var mazeData2D = [];
                for (var i = 0; i < rows; i++) {
                    var row = [];
                    for (var j = 0; j < cols; j++) {
                        row.push(mazeData[i * cols + j]);
                    }
                    mazeData2D.push(row);
                }

                if (mazeData2D && mazeData2D.length > 0 && mazeData2D[0] && mazeData2D[0].length > 0) {
                    var divider = (mazeData2D.length > mazeData2D[0].length) ? mazeData2D.length : mazeData2D[0].length;
                    var cellSize = canvas.width / divider;

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

                    if (startPoint) {
                        ctx.fillStyle = "green";
                        ctx.fillRect(startPoint.x * cellSize, startPoint.y * cellSize, cellSize, cellSize);
                    }
                    if (endPoint) {
                        ctx.fillStyle = "red";
                        ctx.fillRect(endPoint.x * cellSize, endPoint.y * cellSize, cellSize, cellSize);
                    }

                    var path = View.vectorToVariantList();
                    if (path.length > 0) {
                        ctx.strokeStyle = "blue";
                        ctx.lineWidth = 2;
                        ctx.beginPath();
                        var start = path[0];
                        var startX = start.x * cellSize + cellSize / 2;
                        var startY = start.y * cellSize + cellSize / 2;
                        ctx.moveTo(startX, startY);
                        for (var i = 1; i < path.length; i++) {
                            var pos = path[i];
                            var x = pos.x * cellSize + cellSize / 2;
                            var y = pos.y * cellSize + cellSize / 2;
                            ctx.lineTo(x, y);
                        }
                        ctx.stroke();
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    var cellSize = canvas.width / canvas.rows;
                    var x = Math.floor(mouse.x / cellSize);
                    var y = Math.floor(mouse.y / cellSize);
                    if (!canvas.startPoint) {
                        canvas.startPoint = {x: x, y: y};
                    } else if (!canvas.endPoint) {
                        canvas.endPoint = {x: x, y: y};
                    } else {
                        canvas.startPoint = null;
                        canvas.endPoint = null;
                    }
                    canvas.requestPaint();
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
                    onClicked: saveFile.open()
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
                    onClicked: loadFile.open()
                }

                FileDialog {
                    id: loadFile
                    title: "Choose a file with maze"
                    fileMode: FileDialog.OpenFile
                    defaultSuffix: "txt"
                    nameFilters: ["Text files (*.txt)"]
                    onAccepted: {
                        var fileUrl = loadFile.file.toString();
                        var filePath = fileUrl.replace(/^(file:\/{2})|(qrc:\/{2})|(http:\/{2})/, "");
                        var filePathString = filePath.toString();
                        View.loadMazeFromFile(filePathString);
                        rowsSpinBox.value = View.getHeight();
                        colsSpinBox.value = View.getWidth();
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
                    id: rowsSpinBox
                    Layout.alignment: Qt.AlignRight
                    Layout.fillWidth: true
                    editable: true
                    from: 1
                    to: 50
                    onValueChanged: View.mazeHeight = value
                }
            }

            RowLayout {
                Text {
                    text: "Maze cols:"
                    Layout.preferredWidth: 80
                }
                SpinBox {
                    id: colsSpinBox
                    Layout.alignment: Qt.AlignRight
                    Layout.fillWidth: true
                    editable: true
                    from: 1
                    to: 50
                    onValueChanged: View.mazeWidth = value
                }
            }

            Button {
                id: generateButton
                text: "Generate"
                font.pixelSize: 18
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                onClicked: View.generateMaze()
            }

            Button {
                id: findWayButton
                text: "Find Path"
                font.pixelSize: 18
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                onClicked: {
                    if (canvas.startPoint && canvas.endPoint) {
                        View.findPath(canvas.startPoint, canvas.endPoint);
                    }
                }
            }

            Button {
                text: "Open Cave Window"
                font.pixelSize: 18
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignHCenter
                onClicked: caveWindow.show()
            }
        }
    }

    // ++++++++++++++CAVE WINDOW++++++++++++++

    Window {
        id: caveWindow
        width: 800
        height: 540
        visible: false
        title: qsTr("Cave")

        Connections {
            target: View
            function onCaveDataChanged() {
                canvasCave.requestPaint();
            }
        }

        RowLayout {
            id: rowLayoutCave
            spacing: 12
            anchors.margins: 16
            anchors.fill: parent

            Canvas {
                id: canvasCave
                width: 500
                height: 500
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

                onPaint: {
                    var ctx = getContext("2d");
                    if (!ctx) return;

                    ctx.fillStyle = "grey";
                    ctx.fillRect(0, 0, width, height);
                    ctx.clearRect(0, 0, width, height);

                    var caveData = View.getCaveData();
                    var rows = heightCountSpinBox.value;
                    var cols = widthCountSpinBox.value;

                    var caveData2D = [];
                    for (var i = 0; i < rows; i++) {
                        var row = [];
                        for (var j = 0; j < cols; j++) {
                            row.push(caveData[i * cols + j]);
                        }
                        caveData2D.push(row);
                    }

                    if (caveData2D && caveData2D.length > 0 && caveData2D[0] && caveData2D[0].length > 0) {
                        var divider = (caveData2D.length > caveData2D[0].length) ? caveData2D.length : caveData2D[0].length;
                        var cellSize = canvasCave.width / divider;

                        for (var i = 0; i < caveData2D.length; i++) {
                            for (var j = 0; j < caveData2D[i].length; j++) {
                                var cell = caveData2D[i][j];
                                var x = j * cellSize;
                                var y = i * cellSize;

                                if (cell) {
                                    ctx.fillStyle = "black";
                                } else {
                                    ctx.fillStyle = "grey";
                                }

                                ctx.fillRect(x, y, cellSize, cellSize);
                            }
                        }
                    }
                }
            }

            ColumnLayout {
                spacing: 12
                Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

                RowLayout {
                    id: buttonRowCave
                    spacing: 12
                    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

                    Button {
                        id: saveButtonCave
                        text: "Save"
                        font.pixelSize: 18
                        onClicked: saveFileCave.open()
                    }

                    FileDialog {
                        id: saveFileCave
                        title: "Save cave in file"
                        fileMode: FileDialog.SaveFile
                        nameFilters: ["Text files (*.txt)"]
                        onAccepted: {
                            var filePath = saveFileCave.file.toString();
                            if (filePath.startsWith("file://")) {
                                filePath = filePath.substring(7);
                            }
                            View.saveCaveInFile(filePath);
                        }
                    }

                    Button {
                        id: loadButtonCave
                        text: "Load"
                        font.pixelSize: 18
                        onClicked: loadFileCave.open()
                    }

                    FileDialog {
                        id: loadFileCave
                        title: "Choose a file with cave"
                        fileMode: FileDialog.OpenFile
                        defaultSuffix: "txt"
                        nameFilters: ["Text files (*.txt)"]
                        onAccepted: {
                            var fileUrl = loadFileCave.file.toString();
                            var filePath = fileUrl.replace(/^(file:\/{2})|(qrc:\/{2})|(http:\/{2})/, "");
                            var filePathString = filePath.toString();
                            View.loadCaveFromFile(filePathString);
                            heightCountSpinBox.value = View.getCaveHeight();
                            widthCountSpinBox.value = View.getCaveWidth();
                        }
                    }
                }

                Text {
                    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
                    text: "Generation settings:"
                }

                RowLayout {
                    Text {
                        text: "Cave rows:"
                        Layout.preferredWidth: 80
                    }
                    SpinBox {
                        id: heightCountSpinBox
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        editable: true
                        from: 1
                        to: 50
                        onValueChanged: View.caveHeight = value
                    }
                }

                RowLayout {
                    Text {
                        text: "Cave width:"
                        Layout.preferredWidth: 80
                    }
                    SpinBox {
                        id: widthCountSpinBox
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        editable: true
                        from: 1
                        to: 50
                        onValueChanged: View.caveWidth = value
                    }
                }

                RowLayout {
                    Text {
                        text: "Init chance:"
                        Layout.preferredWidth: 80
                    }
                    Slider {
                        id: initChanceSlider
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        from: 0
                        to: 100
                        onValueChanged: View.setInitChance(value)
                    }
                }

                RowLayout {
                    Text {
                        text: "Born limits:"
                        Layout.preferredWidth: 80
                    }
                    SpinBox {
                        id: bornCountSpinBox
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        editable: true
                        from: 0
                        to: 7
                        onValueChanged: View.setBornLimits(value)
                    }
                }

                RowLayout {
                    Text {
                        text: "Life limits:"
                        Layout.preferredWidth: 80
                    }
                    SpinBox {
                        id: lifeCountSpinBox
                        Layout.alignment: Qt.AlignRight
                        Layout.fillWidth: true
                        editable: true
                        from: 0
                        to: 7
                        onValueChanged: View.setLifeLimits(value)
                    }
                }

                Button {
                    id: generateButtonCave
                    text: "Generate"
                    font.pixelSize: 18
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignHCenter
                    onClicked: View.generateCave()
                }
            }
        }
    }
}