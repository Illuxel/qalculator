import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

import qalculator.style

import qalculator.History
import qalculator.Converter

ApplicationWindow {
    id: mainWindow

    width: 335
    height: 505

    minimumWidth: 335
    minimumHeight: 505

    maximumWidth: 335
    maximumHeight: 505

    visible: true
    color: "transparent"

    background: Rectangle {
        color: "#1f1f27"
        topLeftRadius: 12.5
        topRightRadius: 12.5
    }

    header: RowLayout {
        spacing: 0
        height: 50
        // drawer button
        StyledDrawerButton {
            id: drawerButton

            iconSource: "qrc:/icons/icon_menu.png"

            Layout.leftMargin: 6
            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft

            onClicked: {
                if (drawerMainList.opened)
                    drawerMainList.close();
                else
                    drawerMainList.open();
            }
        }
        // Status of opened tab
        Label {
            id: calcType

            text: "Standart"
            color: "#e5e5e5"
            font.bold: true
            font.pixelSize: 20

            Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
            Layout.leftMargin: 5
            Layout.minimumWidth: 150
        }

        Item {
            Layout.fillWidth: true
        }

        // History
        StyledDrawerButton {
            id: historyButton

            Layout.rightMargin: 6
            Layout.alignment: Qt.AlignVCenter | Qt.AlignRight

            iconSource: "qrc:/icons/icon_history.png"
            onClicked: {
                historyListView.model = History.list;
                drawerHistory.open();
            }
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: drawerList.model.get(0).page // by default using standart calculator
        clip: true
    }

    Drawer {
        id: drawerMainList

        width: parent.width * 0.75
        height: parent.height
        edge: Qt.LeftEdge

        modal: true
        dim: true
        interactive: true

        background: Rectangle {
            topRightRadius: 12.5
            bottomRightRadius: 12.5
            color: "#2e2e2e"
        }

        ColumnLayout {
            anchors.fill: parent

            ListView {
                id: drawerList

                clip: true
                spacing: 4

                Layout.fillWidth: true
                Layout.fillHeight: true

                Layout.topMargin: 25
                Layout.leftMargin: 10
                Layout.rightMargin: 10

                model: ListModel {
                    ListElement {
                        name: "Standart"
                        icosource: "qrc:/icons/icon_calculator.png"
                        page: "qrc:/qalculator/app/qml/page/Calculator.qml"
                        section: "Calculators"
                    }
                    ListElement {
                        name: "Angle"
                        icosource: "qrc:/icons/icon_angle.png"
                        page: "qrc:/qalculator/app/qml/page/Converter.qml"
                        section: "Converters"
                    }
                    ListElement {
                        name: "Data"
                        icosource: "qrc:/icons/icon_data.png"
                        page: "qrc:/qalculator/app/qml/page/Converter.qml"
                        section: "Converters"
                    }
                }

                section.property: "section"
                section.criteria: ViewSection.FullString
                section.delegate: Rectangle {
                    height: 28
                    color: "transparent"

                    required property string section

                    Text {
                        text: section
                        color: "white"
                        font.pixelSize: 14
                    }
                }

                delegate: StyledToolButton {
                    iconSource: icosource
                    iconH: 28
                    iconW: 28
                    width: drawerList.width
                    height: 48
                    textButton: name
                    textBold: false

                    textLeftMargin: 5
                    imageLeftMargin: 5

                    textItemAlign: Qt.AlignLeft

                    onClicked: {
                        drawerMainList.close();

                        if (drawerList.section == "Calculators")
                            historyButton.visible = true;
                        else
                            historyButton.visible = false;

                        if (section == "Converters")
                            Converter.currentConverter = name;

                        stackView.pop();
                        stackView.push(page);
                        calcType.text = name;
                    }
                }
            }

            StyledToolButton {
                id: settingsButton

                textButton: "Settings"
                textBold: false

                iconSource: "qrc:/icons/icon_settings.png"

                contentSpacing: 5
                imageLeftMargin: 5
                textItemAlign: Qt.AlignLeft

                Layout.fillWidth: true
                Layout.margins: 10
                Layout.minimumHeight: 40
                Layout.maximumHeight: 40

                onClicked: {}
            }
        }
    }

    Drawer {
        id: drawerHistory
        width: mainWindow.width
        height: 310
        modal: true
        interactive: true
        edge: Qt.BottomEdge
        background: Rectangle {
            topLeftRadius: 12.5
            topRightRadius: 12.5
            color: "#2e2e2e"
            border.color: "grey"
        }

        ListView {
            id: historyListView
            anchors.centerIn: parent
            width: 250
            height: parent.height
            clip: true
            spacing: 5
            delegate: StyledToolButton {
                width: parent.width
                height: 48
                textButton: modelData

                textLeftMargin: 5
                textItemAlign: Qt.AlignLeft

                onClicked: {
                    History.currentItem = modelData;
                    drawerHistory.close();
                }
            }
        }
    }
}
