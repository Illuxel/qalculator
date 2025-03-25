import QtQuick
import QtQuick.Controls

ItemDelegate {
    property color fontColor: "white"
    background: Rectangle {
        color: hovered ? Qt.lighter("#2e2e2e", 2) : "#2e2e2e"
        radius: 5
    }
    contentItem: Text {
        text: modelData
        color: fontColor
        elide: Text.ElideRight
        font.pixelSize: 14
        verticalAlignment: Text.AlignVCenter
    }
}
