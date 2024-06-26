import QtQuick
import QtQuick.Controls
import Qt.labs.platform

import weatherGui

ApplicationWindow {
    id: appWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Weather app")

    MenuBar {
        Menu {
            title: qsTr("File")

            MenuItem {
                text: qsTr("Edit settings")
                onTriggered: settingsPopup.open()
            }
        }
    }

    function hasBeenSetUp() {
        return AppSettings.apiKey && AppSettings.locationParam
    }

    Loader {
        active: !hasBeenSetUp()
        sourceComponent: startScreen
    }
    Loader {
        active: hasBeenSetUp()
        sourceComponent: weatherForecastScreen
    }

    Component {
        id: startScreen
        Start {
            win: appWindow
            onOpenSettingsPopup: settingsPopup.open()
        }
    }

    Component {
        id: weatherForecastScreen
        WeatherForecast {
            win: appWindow
        }
    }

    SettingsPopup {
        id: settingsPopup
        anchors.centerIn: Overlay.overlay
        visible: false
    }
}
