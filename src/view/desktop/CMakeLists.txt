cmake_minimum_required(VERSION 3.14)
 
project(Maze LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
# Добавляем пакет Quick
find_package(Qt6 6.4 REQUIRED COMPONENTS Quick)
 
qt_standard_project_setup()
 
# Определяем компилируемые файлы
qt_add_executable(Maze
  main.cc
  ../../model/maze.cc
  ../../controller/controller.cc
)
 
# Добавляем файлы qml
qt_add_qml_module(Maze
    URI path      # ссылка, по которой будут загружаться файлы qml
    VERSION 1.0
    QML_FILES main.qml
)
 
target_link_libraries(Maze
    PRIVATE Qt6::Quick
)
 
include(GNUInstallDirs)
install(TARGETS Maze
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)