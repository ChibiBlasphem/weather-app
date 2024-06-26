import QtQuick
import QtQuick.Controls

import weatherGui

Screen {
    signal openSettingsPopup()

    Column {
        anchors.centerIn: parent

        Label {
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: 20
            text: qsTr("No API has been set")
        }

        Button {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Set an API key")
            onClicked: {
                openSettingsPopup()
            }
        }
    }
}
