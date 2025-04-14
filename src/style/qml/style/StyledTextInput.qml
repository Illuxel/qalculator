import QtQuick

Rectangle {
    id: textInputStyle

    signal textEdited
    signal accepted
    signal editingFinished

    function length() {
        return textInput.length;
    }
    function remove(start, end) {
        textInput.remove(start, end);
    }
    function clear() {
        textInput.clear();
    }

    property bool allowInput: false

    property string inputText: ""
    property color textColor: "#e5e5e5"
    property bool textBold: true
    property real textSize: 34

    property int maxLength: 16

    property bool inputFocused: false

    property color backColor: "transparent"
    property color hoverColor: "transparent"
    property color borderColor: "white"

    clip: true

    radius: 5
    color: textInputStyle.hovered ? ((hoverColor === "") ? Qt.lighter(baseColor, 1.18) : hoverColor) : backColor
    border.color: textInputStyle.hovered ? borderColor : backColor

    TextInput {
        id: textInput
        anchors.fill: parent
        anchors.margins: 1
        clip: true

        readOnly: allowInput

        text: inputText
        maximumLength: maxLength

        focus: inputFocused

        color: textColor
        font.bold: textBold
        font.pixelSize: textSize

        validator: RegularExpressionValidator {
            regularExpression: /^[0-9]*$/
        }

        onAccepted: {
            textInputStyle.inputText = textInput.text;
            textInputStyle.accepted();
        }
        onTextEdited: {
            textInputStyle.inputText = textInput.text;
            textInputStyle.textEdited();
        }
        onEditingFinished: {
            textInputStyle.inputText = textInput.text;
            textInputStyle.editingFinished();
        }
    }
}
