import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import weatherGui

Screen {
    id: screen

    Loader {
        active: !!forecast.data.current
        sourceComponent: display

        Component {
            id: display

            Item {
                width: screen.width; height: screen.height;

                RowLayout {
                    id: currentWeather
                    width: parent.width;
                    height: parent.height / 3 * 2

                    Item {
                        width: parent.width / 2
                        Layout.fillHeight: true

                        Image {
                            width: 200
                            height: 200
                            anchors.centerIn: parent
                            source: `https:${forecast.data.current.condition.icon}`
                        }
                    }

                    Item {
                        width: parent.width / 2
                        Layout.fillHeight: true

                        Label {
                            anchors.centerIn: parent
                            font.pixelSize: 40
                            text: qsTr("%L1 °c").arg(forecast.data.current.temp_c)
                        }
                    }
                }

                RowLayout {
                    id: grid
                    width: parent.width;
                    height: parent.height / 3
                    anchors.top: currentWeather.bottom

                    Repeater {
                        id: forecastListView
                        model: forecast.forecast.slice(1)

                        Column {
                            id: forecastDay
                            width: grid.width / 6
                            Layout.fillWidth: true
                            
                            required property var modelData

                            Label {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("%1").arg(new Date(forecastDay.modelData.date).toLocaleDateString(Qt.locale(), "ddd"))
                            }
                            Image {
                                anchors.horizontalCenter: parent.horizontalCenter
                                source: `https:${forecastDay.modelData.day.condition.icon}`
                            }
                            Label {
                                anchors.horizontalCenter: parent.horizontalCenter
                                text: qsTr("%L1 °c").arg(forecastDay.modelData.day.avgtemp_c)
                            }
                        }
                    }
                }
            }
        }
    }

    RestManager {
        id: restManager
        url: "http://api.weatherapi.com/v1/"

        ResourceWithParams {
            id: forecast
            path: "forecast.json"

            Param { name: "q"; value: AppSettings.locationParam }
            Param { name: "days"; value: "7" }
        }
    }

    Component.onCompleted: forecast.refreshData()
}
