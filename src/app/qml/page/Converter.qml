import QtQml.Models
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import qalculator.style

import qalculator.Converter
import qalculator.ConverterHandler

Page {
    id: page

    background: Rectangle {
        color: "transparent"
    }

    Converter {
        id: converter

        onInputValueChanged: firstTypeInput.inputText = converter.inputValue
        onLastConvertedChanged: secondTypeInput.inputText = converter.convertedValue
        onSchemeLoaded: secondTypeBox.model = converter.typeList

        Component.onCompleted: {
            converter.setScheme(ConverterHandler.getScheme());
            converter.secondType = secondTypeBox.textAt(0);
        }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 1
        //
        StyledTextInput {
            id: firstTypeInput
            Layout.fillWidth: true
            Layout.minimumHeight: 32
            Layout.margins: 10
            textSize: 30

            onTextEdited: converter.processInput(firstTypeInput.inputText)
        }
        //
        Rectangle {
            color: "white"
            Layout.fillWidth: true
            Layout.minimumHeight: 2
            Layout.margins: 5
            Layout.leftMargin: 10
            Layout.rightMargin: 10
        }
        //
        StyledTextInput {
            id: secondTypeInput
            Layout.fillWidth: true
            Layout.minimumHeight: 32
            Layout.margins: 10
            textSize: 32
            allowInput: true
        }
        StyledComboBox {
            id: secondTypeBox
            Layout.minimumWidth: 100
            Layout.minimumHeight: 35
            Layout.leftMargin: 10

            onActivated: converter.secondType = secondTypeBox.textAt(currentIndex)
        }
        //
        Rectangle {
            id: gridInputStyle
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: "transparent"
            GridView {
                id: gridView
                anchors.fill: parent
                anchors.margins: 10

                cellHeight: gridView.height / 5
                cellWidth: gridView.width / 3

                interactive: false

                model: ListModel {
                    ListElement {
                        ph: ""
                        color: "transparent"
                    }
                    ListElement {
                        ph: "CE"
                        type: "cmd"
                        func: "clr"
                        color: "#31313d"
                    }
                    ListElement {
                        ph: "Del"
                        type: "cmd"
                        func: "del"
                        color: "#c42b1c"
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
                        ph: ""
                        color: "transparent"
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
                }
                delegate: StyledToolButton {
                    height: 40
                    width: 96
                    iconH: 0
                    iconW: 0
                    fluentThikness: 0.89
                    textButton: ph

                    textItemAlign: Qt.AlignHCenter

                    enabled: (ph == "") ? false : true
                    visible: (ph == "") ? false : true

                    baseColor: (color === "") ? StyledToolButton.baseColor : color

                    onClicked: {
                        if (type === "cmd") {
                            if (func === "del") {
                                firstTypeInput.remove(firstTypeInput.length() - 1, firstTypeInput.length());

                                if (firstTypeInput.length() == 0)
                                    firstTypeInput.inputText = "0";
                            } else if (func === "clr")
                                firstTypeInput.clear();
                        } else {
                            firstTypeInput.inputText += ph;
                            converter.processInput(firstTypeInput.inputText);
                        }
                    }
                }
            }
        }
    }
}
