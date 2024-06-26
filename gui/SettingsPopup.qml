import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Popup {
    id: settingsPopup
    width: 300
    height: 400
    padding: 20

    ColumnLayout {
        RowLayout {
            Label {
                Layout.alignment: Qt.AlignVCenter
                text: qsTr("API Key")
            }
            TextField {
                text: AppSettings.apiKey
                onEditingFinished: { AppSettings.apiKey = text }
            }
        }

        RowLayout {
            Label {
                Layout.alignment: Qt.AlignVCenter
                text: qsTr("Location")
            }
            TextField {
                text: AppSettings.locationParam
                onEditingFinished: { AppSettings.locationParam = text }
            }
        }
    }
}
