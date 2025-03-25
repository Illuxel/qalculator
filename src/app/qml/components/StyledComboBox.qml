import QtQuick
import QtQuick.Controls

import "../components" as Calculator

ComboBox {
    id: comboBox

    delegate: Calculator.StyledComboItem {
        width: comboBox.width
        fontColor: "white"
        highlighted: comboBox.highlightedIndex === index
    }

    indicator: Canvas {
        id: canvas
        x: comboBox.width - width - comboBox.rightPadding
        y: comboBox.topPadding + (comboBox.availableHeight - height) / 2
        width: 12
        height: 8
        contextType: "2d"
        Connections {
            target: comboBox
            function onPressedChanged() {
                canvas.requestPaint();
            }
        }
        onPaint: {
            context.reset();
            context.moveTo(0, 0);
            context.lineTo(width, 0);
            context.lineTo(width / 2, height);
            context.closePath();
            context.fillStyle = "white";
            context.fill();
        }
    }

    contentItem: Text {
        leftPadding: 0
        rightPadding: comboBox.indicator.width + comboBox.spacing
        text: comboBox.displayText
        font.pixelSize: 14
        color: "white"
        verticalAlignment: Text.AlignVCenter
        elide: Text.ElideRight
    }

    background: Rectangle {
        radius: 5
        color: comboBox.hovered ? Qt.lighter("#2e2e2e", 1.18) : "#2e2e2e"
        border.color: comboBox.pressed ? "white" : "tranparent"
        border.width: comboBox.visualFocus ? 2 : 1
    }

    popup: Popup {
        y: comboBox.height - 2
        implicitWidth: comboBox.width
        implicitHeight: contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            spacing: 3
            implicitWidth: contentWidth * 1.1
            implicitHeight: contentHeight
            model: comboBox.popup.visible ? comboBox.delegateModel : null
            currentIndex: comboBox.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator {}
        }

        background: Rectangle {
            color: Qt.lighter("#1f1f27", 1.18)
            radius: 5
        }
    }
}
