import QtQuick
import QtQuick.Controls

Item {
    id: root
    width: 800
    height: 600

    property var mazeData: [] // Данные лабиринта
    property int cellSize: 20 // Размер ячейки

    Canvas {
        id: canvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d");
            ctx.clearRect(0, 0, width, height);
            ctx.strokeStyle = "black";
            ctx.lineWidth = 2;

            for (var row = 0; row < mazeData.length; row++) {
                for (var col = 0; col < mazeData[row].length; col++) {
                    var cell = mazeData[row][col];
                    var x = col * cellSize;
                    var y = row * cellSize;

                    // Рисуем правую стену
                    if (cell.rightWall) {
                        ctx.beginPath();
                        ctx.moveTo(x + cellSize, y);
                        ctx.lineTo(x + cellSize, y + cellSize);
                        ctx.stroke();
                    }

                    // Рисуем нижнюю стену
                    if (cell.bottomWall) {
                        ctx.beginPath();
                        ctx.moveTo(x, y + cellSize);
                        ctx.lineTo(x + cellSize, y + cellSize);
                        ctx.stroke();
                    }
                }
            }
        }
    }

    // Обновляем данные лабиринта и перерисовываем
    function updateMaze(newMazeData) {
        mazeData = newMazeData;
        canvas.requestPaint();
    }
}