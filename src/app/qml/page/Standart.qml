import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import qalculator.style

import qalculator.History
import qalculator.Standart

Page {
    id: page

    Standart {
        id: calcStandart

        onEnteredValueChanged: finalTextInput.text = calcStandart.enteredValue
        onFinalValueChanged: finalTextInput.text = calcStandart.finalValue
        onLastOperationChanged: lastTextInput.text = calcStandart.lastOperation

        Component.onCompleted: {
            calcStandart.setHistory(History.object);
            calcStandart.update();
        }
    }

    background: Rectangle {
        color: "transparent"
    }
    ColumnLayout {
        anchors.fill: parent
        spacing: 6
        // last operation
        Rectangle {
            id: lastTextInputStyle
            Layout.fillWidth: true
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            Layout.minimumHeight: parent.height * 0.06
            Layout.alignment: Qt.AlignCenter
            clip: true
            color: "transparent"
            TextInput {
                id: lastTextInput
                anchors.fill: parent
                horizontalAlignment: Qt.AlignRight
                verticalAlignment: Qt.AlignBottom
                readOnly: true
                clip: true
                color: Qt.darker("#e5e5e5", 0.4)
                font.bold: true
                font.pixelSize: 17
            }
        }
        // text input
        Rectangle {
            id: finalTextInputStyle
            Layout.fillWidth: true
            Layout.leftMargin: 20
            Layout.rightMargin: 20
            Layout.minimumHeight: parent.height * 0.14
            Layout.alignment: Qt.AlignCenter
            clip: true
            color: "transparent"
            TextInput {
                id: finalTextInput
                anchors.fill: parent
                horizontalAlignment: Qt.AlignRight
                verticalAlignment: Qt.AlignBottom
                clip: true
                focus: true
                color: "#e5e5e5"
                font.bold: true
                font.pixelSize: 34
                maximumLength: 14
                validator: RegularExpressionValidator {
                    regularExpression: /^[0-9]*$/
                }

                onAccepted: calcStandart.getEqual()

                onTextEdited: {
                    let temp = text;

                    if (finalTextInput.getText(0, 1) == '.')
                        finalTextInput.clear();

                    finalTextInput.text = temp;
                    calcStandart.enteredValue = temp;
                }
                onEditingFinished: {
                    if (finalTextInput.length == 0)
                        finalTextInput.text = '0';
                    if (finalTextInput.getText(0, 1) == '0')
                        finalTextInput.remove(0, 1);
                }
            }
        }
        // grid buttons view
        Rectangle {
            id: gridInputStyle
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
            GridView {
                id: gridView
                anchors.fill: parent
                anchors.margins: 10
                interactive: false
                cellHeight: gridView.height / 6
                cellWidth: gridView.width / 4

                model: ListModel {
                    ListElement {
                        ph: "%"
                        type: "function"
                        func: "%1/100"
                        color: ""
                    }
                    ListElement {
                        ph: "CE"
                        type: "cmd"
                        func: "clr"
                        color: ""
                    }
                    ListElement {
                        ph: "C"
                        type: "cmd"
                        func: "clrall"
                        color: ""
                    }
                    ListElement {
                        ph: "Del"
                        type: "cmd"
                        func: "del"
                        color: "#c42b1c"
                    }
                    ListElement {
                        ph: "1/x"
                        type: "function"
                        func: "1/(%1)"
                        color: ""
                    }
                    ListElement {
                        ph: "x^2"
                        type: "function"
                        func: "Math.pow(%1, 2)"
                        color: ""
                    }
                    ListElement {
                        ph: "2√"
                        type: "function"
                        func: "Math.sqrt(%1)"
                        color: ""
                    }
                    ListElement {
                        ph: "÷"
                        type: "operator"
                        func: "/"
                        color: ""
                    }
                    ListElement {
                        ph: "7"
                        type: "value"
                        func: "7"
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "8"
                        type: "value"
                        func: "8"
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "9"
                        type: "value"
                        func: "9"
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "x"
                        type: "operator"
                        func: "*"
                        color: ""
                    }
                    ListElement {
                        ph: "4"
                        type: "value"
                        func: "4"
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "5"
                        type: "value"
                        func: "5"
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "6"
                        type: "value"
                        func: "6"
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "-"
                        type: "operator"
                        func: "-"
                        color: ""
                    }
                    ListElement {
                        ph: "1"
                        type: "value"
                        func: "1"
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "2"
                        type: "value"
                        func: "2"
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "3"
                        type: "value"
                        func: "3"
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "+"
                        type: "operator"
                        func: "+"
                        color: ""
                    }
                    ListElement {
                        ph: "+/-"
                        type: "cmd"
                        func: "cnvrt"
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "0"
                        type: "value"
                        func: "0"
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "."
                        type: "value"
                        func: "."
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "="
                        type: "cmd"
                        func: "equal"
                        color: "#afadcc"
                    }
                }
                delegate: StyledToolButton {
                    height: 46
                    width: 72
                    iconH: 0
                    iconW: 0
                    fluentThikness: 0.89
                    textButton: ph
                    textItemAlign: Qt.AlignHCenter
                    baseColor: (color === "") ? StyledToolButton.baseColor : color

                    onClicked: calcStandart.processButton(type, func, ph)
                }
            }
        }
    }
}
