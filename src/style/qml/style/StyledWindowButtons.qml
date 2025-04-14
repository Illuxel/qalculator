import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

ToolButton {
    id: styledButton

    property string iconSource: ""

    property int iconWidth: 20
    property int iconHight: 20

    property string baseColor: "transparent"
    property string hoverColor: ""

    contentItem: Image {
        source: iconSource

        sourceSize.width: iconWidth
        sourceSize.height: iconHight

        fillMode: Image.PreserveAspectFit
    }

    background: Rectangle {
        color: styledButton.hovered ? Qt.lighter((hoverColor === "") ? baseColor : hoverColor, 1.25) : baseColor
    }
}
