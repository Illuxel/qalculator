import QtQuick
import QtQuick.Controls

ToolButton {
    id: styledButton

    property string iconSource: ""

    property int iconW: 24
    property int iconH: 24

    property color baseColor: "#1f1f27"
    property color hoverColor: "#2e2e37"

    icon {
        color: "#e5e5e5"
        source: iconSource
        width: iconW
        height: iconH
    }

    background: Rectangle {
        color: styledButton.hovered ? "#2e2e37" : baseColor
        radius: 5
    }
}
