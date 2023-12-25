cmake_minimum_required(VERSION 3.28)

project(KCRM VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Sql PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql PrintSupport)

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
        src/data_base/data_base_manager_kcrm.h
        src/data_base/data_base_manager_kcrm.cpp
        src/logger_monitor.h
        src/logger_monitor.cpp
        resource.qrc
        src/other_widgets/widget_users.hpp
        src/other_widgets/widget_users.ui
)
add_executable(KCRM ${PROJECT_SOURCES}
    scripts/AI_test.py)

if (WIN32)
    message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ OS Windows ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/third-party/QPSQL/libiconv-2.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/third-party/QPSQL/libintl-9.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/third-party/QPSQL/libpq.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>)
else()
    message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ OS Linux ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
endif (WIN32)
message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ You Qt version " ${QT_VERSION_MAJOR}.${QT_VERSION_MINOR} " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
message("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Cmake version " ${CMAKE_VERSION} " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")

#Для работы с excel документами
add_subdirectory(third-party/QXlsx/)
target_link_libraries(${PROJECT_NAME} PRIVATE QXlsx::QXlsx)

target_link_libraries(KCRM PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::PrintSupport)

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

add_custom_command(
   TARGET ${PROJECT_NAME} POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy
   ${CMAKE_CURRENT_SOURCE_DIR}/network_settings.json
   $<TARGET_FILE_DIR:${PROJECT_NAME}>)

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
   ${CMAKE_CURRENT_SOURCE_DIR}/scripts/
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/scripts)

