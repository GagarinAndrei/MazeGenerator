import QtQuick 2.15
import QtQuick.Controls 2.15
import com.example.maze 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600

    Maze {
        id: mazeLogic
        onGenerated: {
            console.log("Лабиринт сгенерирован");
            mazeCanvas.updateMaze(); // Обновляем отрисовку после генерации
        }
    }

    Rectangle {
        width: parent.width
        height: parent.height
        color: "lightgray"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                // Обработка клика по лабиринту
                let cell = mazeLogic.getCell(mouse.y / cellHeight, mouse.x / cellWidth);
                console.log("Кликнули по ячейке:", cell.set);
            }
        }
        
        Button {
            text: "Сгенерировать лабиринт"
            onClicked:{ 
                mazeLogic.setSize(10, 10);
                mazeLogic.generate();
            }
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
        }
        
        // Вычисление размеров ячеек (например)
        property real cellHeight: height / mazeLogic.getHeight()
        property real cellWidth: width / mazeLogic.getWidth()

        // Компонент для отрисовки лабиринта
        Rectangle {
            id: mazeCanvas
            anchors.fill: parent

            function updateMaze() {
                // Очищаем предыдущую отрисовку
                children.forEach(child => child.destroy());
                
                for (let y = 0; y < mazeLogic.getHeight(); y++) {
                    for (let x = 0; x < mazeLogic.getWidth(); x++) {
                        let cell = mazeLogic.getCell(y, x);
                        if (cell.isWall) {
                            // Создаем стену для ячейки с wall
                            Rectangle {
                                width: cellWidth
                                height: cellHeight
                                color: "black"
                                x: x * cellWidth
                                y: y * cellHeight
                            }
                        } else {
                            // Создаем пустую ячейку (можно добавить цвет или другие элементы)
                            Rectangle {
                                width: cellWidth
                                height: cellHeight
                                color: "white"
                                x: x * cellWidth
                                y: y * cellHeight
                            }
                        }
                    }
                }
            }
        }
    }
}
