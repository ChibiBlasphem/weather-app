cmake_minimum_required(VERSION 3.16)

project(
  WeatherApp
  VERSION 1.0.0
  LANGUAGES CXX)

find_package(Qt6 6.7 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_add_executable(WeatherApp main.cpp)

set_source_files_properties(gui/AppSettings.qml PROPERTIES QT_QML_SINGLETON_TYPE
                                                           TRUE)

qt_add_qml_module(
  WeatherApp
  URI
  weatherGui
  QML_FILES
  gui/Main.qml
  gui/AppSettings.qml
  gui/Screen.qml
  gui/SettingsPopup.qml
  gui/screens/Start.qml
  gui/screens/WeatherForecast.qml
  SOURCES
  AbstractResource.h
  RestManager.h
  RestManager.cpp
  ResourceWithParams.h
  Param.h)

target_link_libraries(WeatherApp PRIVATE Qt6::Quick)
