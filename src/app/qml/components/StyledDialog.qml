import QtQuick
import QtQuick.Controls

Dialog {
    id: dialog

    background: Rectangle {
        color: "#252526"
        border.color: "#3a3a3a"
        opacity: 0.93
        radius: 5
    }

    header: Rectangle {
        color: "red"

        Text {
            anchors.fill: parent
            text: "text"
        }
    }

    contentItem: Text {}
}
