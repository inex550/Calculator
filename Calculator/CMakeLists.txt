cmake_minimum_required(VERSION 3.5)

project(SmartCalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp

    CalcScreen/calcwindow.cpp
    CalcScreen/calcwindow.h
    CalcScreen/calcwindow.ui
    CalcScreen/calccontroller.h
    CalcScreen/calccontroller.cpp

    CreditScreen/creditwindow.cpp
    CreditScreen/creditwindow.h
    CreditScreen/creditwindow.ui
    CreditScreen/creditcontroller.h
    CreditScreen/creditcontroller.cpp
    CreditScreen/creditmodel.h
    CreditScreen/creditmodel.cpp

    DepositScreen/depositwindow.cpp
    DepositScreen/depositwindow.h
    DepositScreen/depositwindow.ui
    DepositScreen/depositcontroller.h
    DepositScreen/depositcontroller.cpp
    DepositScreen/depositmodel.h
    DepositScreen/depositmodel.cpp
    DepositScreen/addremitemwidget.cpp
    DepositScreen/addremitemwidget.h
    DepositScreen/addremitemwidget.ui
    DepositScreen/addremitem.h

    PlotScreen/plotwindow.cpp
    PlotScreen/plotwindow.h
    PlotScreen/plotwindow.ui
    PlotScreen/plotcontroller.h
    PlotScreen/plotcontroller.cpp

    notationmodel.h
    notationmodel.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SmartCalc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SmartCalc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SmartCalc SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SmartCalc
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(SmartCalc PRIVATE .)

add_subdirectory(qcustomplot)
target_link_libraries(SmartCalc PRIVATE qcustomplot)
target_include_directories(SmartCalc PRIVATE qcustomplot)

add_subdirectory(../NotationLib ${CMAKE_CURRENT_BINARY_DIR}/NotationLib)
target_link_libraries(SmartCalc PRIVATE notation_lib)

target_link_libraries(SmartCalc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(SmartCalc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER app.inex.smartcalc
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS SmartCalc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SmartCalc)
endif()
