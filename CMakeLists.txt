cmake_minimum_required(VERSION 3.5)

project(KCRM VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_PREFIX_PATH "C:/msys64/mingw64/lib/cmake/Qt6")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Sql REQUIRED)


set(PROJECT_SOURCES
        src/main.cpp
        src/kcrm.cpp
        src/kcrm.h
        src/kcrm.ui
        src/widget_create_file.cpp
        src/widget_create_file.h
        src/widget_create_file.ui
        src/widget_text_document.cpp
        src/widget_text_document.h
        src/widget_text_document.ui
        src/widget_table_document.cpp
        src/widget_table_document.h
        src/widget_table_document.ui
        src/widget_minimization_widget.cpp
        src/widget_minimization_widget.h
        src/widget_minimization_widget.ui
        src/widget_telegram/widget_telegram.cpp
        src/widget_telegram/widget_telegram.h
        src/widget_telegram/widget_telegram.ui
        src/data_base/data_base.h
        src/data_base/data_base.cpp
        src/widget_logon.h
        src/widget_logon.cpp
        src/widget_logon.ui
        resource.qrc
)
add_executable(KCRM ${PROJECT_SOURCES})

if (WIN32)
    message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~OS Windows~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
else()
    message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~OS Linux~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
endif (WIN32)
message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~You Qt version ->> " ${QT_VERSION_MAJOR} ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)
message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Cmake version ->> " ${CMAKE_VERSION} ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~)

#Для работы с excel документами
#set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/third-party/QXlsx")
add_subdirectory(third-party/QXlsx/)
target_link_libraries(${PROJECT_NAME} PRIVATE QXlsx::QXlsx)
#Принтер...
find_package(Qt5 COMPONENTS PrintSupport REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::PrintSupport)

target_link_libraries(KCRM PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Sql)



set_target_properties(KCRM PROPERTIES
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(KCRM)
endif()

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
   ${CMAKE_CURRENT_SOURCE_DIR}/res/
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)


