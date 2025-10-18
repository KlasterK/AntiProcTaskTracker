cmake_minimum_required(VERSION 3.16)

project(tracker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    taskitem.h
    edittaskmodel.h
    tasktypedelegate.h
    tasktimedelegate.h
    edittaskmodel.cpp
    tasktypedelegate.cpp
    countingtaskmodel.h
    countingtaskmodel.cpp
)

qt_add_executable(tracker
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

qt_add_resources(tracker "images"
    PREFIX "/"
    FILES
        images/main_icon.png
)

target_link_libraries(tracker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(tracker PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS tracker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(tracker)
