import QtQuick
import QtQuick.Shapes
import QtQuick.Controls
import QtQuick.Layouts

ToolButton {
    id: styledButton

    property string iconSource: ""

    property real iconW: 24
    property real iconH: 24

    property color textColor: "#e5e5e5"
    property color baseColor: "#2e2e2e"
    property color hoverColor: "#2e2e2e"

    property string textButton: ""
    property int textFontSize: 16
    property bool textBold: true

    // margins
    property real imageLeftMargin: 0

    property int imageItemAlign: Qt.AlignLeft
    property bool fillImageWidth: false
    property bool fillImageHeight: false

    // margins
    property real textLeftMargin: 0

    property int textHAlign: Qt.AlignHCenter
    property int textVAlign: Qt.AlignVCenter

    property int textItemAlign: Qt.AlignLeft
    property bool fillTextWidth: false
    property bool fillTextHeight: false

    property real contentSpacing: 0

    property real fluentThikness: 1.0

    background: Rectangle {
        color: styledButton.hovered ? Qt.lighter(baseColor, 1.18) : baseColor
        opacity: fluentThikness
        radius: 5
    }

    contentItem: RowLayout {
        spacing: contentSpacing
        Image {
            smooth: false
            source: iconSource
            sourceSize.width: iconW
            sourceSize.height: iconH
            Layout.leftMargin: imageLeftMargin
            Layout.alignment: imageItemAlign
            Layout.fillHeight: fillImageHeight

            Layout.fillWidth: fillImageWidth
        }
        Text {
            text: textButton
            color: textColor
            font.bold: textBold
            font.pixelSize: textFontSize

            horizontalAlignment: textHAlign
            verticalAlignment: textVAlign

            Layout.fillWidth: fillTextWidth

            Layout.leftMargin: textLeftMargin
            Layout.alignment: textItemAlign
            Layout.fillHeight: fillTextHeight
        }
    }
}
