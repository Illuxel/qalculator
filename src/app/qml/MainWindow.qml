import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

import qalculator.style

import qalculator.History
import qalculator.Converter

ApplicationWindow {
    id: window
    visible: true

    title: "Qalculator"

    width: 335
    height: 505

    minimumWidth: 335
    minimumHeight: 505

    maximumWidth: 335
    maximumHeight: 505

    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint

    // windows
    property int bw: 1

    color: "transparent"

    background: Rectangle {
        //id: bgColor
        color: "#1f1f27"
        radius: 12.5
        border.color: "grey"
        border.width: bw
    }
    // window menu layout
    header: ToolBar {
        id: windowToolBar
        height: 42
        width: window.width
        anchors.margins: 0
        // style
        background: Rectangle {
            color: "transparent"
        }
        Item {
            id: windowToolBarItem
            anchors.fill: parent
            clip: true
            // on move window handler
            DragHandler {
                id: moveHandler
                grabPermissions: TapHandler.TakeOverForbidden
                onActiveChanged: {
                    if (active) {
                        window.startSystemMove();
                    }
                }
            }
            // window menu layout
            RowLayout {
                anchors.fill: parent
                spacing: 0
                Image {
                    id: appIco
                    source: "qrc:/icons/icon_calculator.png"
                    sourceSize.width: 20
                    sourceSize.height: 20
                    Layout.leftMargin: 5
                }
                Text {
                    text: window.title
                    font.pixelSize: 14
                    font.family: "Segoe"
                    color: "white"
                    Layout.leftMargin: 5
                }

                Item {
                    Layout.fillWidth: true
                }

                StyledWindowButtons {
                    iconSource: "qrc:/icons/icon_subtract.png"
                    hoverColor: hovered ? Qt.lighter("#1f1f27", 1.1) : "#1f1f27"
                    Layout.minimumWidth: 42
                    onClicked: window.showMinimized()
                }
                StyledWindowButtons {
                    iconSource: "qrc:/icons/icon_close.png"
                    hoverColor: hovered ? "red" : "#1f1f27"
                    Layout.minimumWidth: 42
                    onClicked: window.close()
                }
            }
        }
    }
    //
    Page {
        id: mainPage
        anchors.fill: parent
        background: Rectangle {
            color: "transparent"
        }
        // calculator tool bar layout
        header: ToolBar {
            id: calcToolBar
            height: 46
            width: window.width
            RowLayout {
                anchors.fill: parent
                spacing: 0
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

                    Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                    Layout.leftMargin: 5
                    Layout.minimumWidth: 150

                    text: "Standart"
                    color: "#e5e5e5"
                    font.bold: true
                    font.pixelSize: 20
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
            background: Rectangle {
                color: "transparent"
            }
        }

        StackView {
            id: stackView
            anchors.fill: parent
            anchors.margins: bw
            clip: true
            initialItem: "qrc:/qalculator/app/qml/page/Standart.qml"
        }

        Drawer {
            id: drawerMainList

            width: 250
            height: parent.height - windowToolBar.height

            y: parent.y - windowToolBar.y

            edge: Qt.LeftEdge

            dim: true
            modal: true
            interactive: false

            background: Rectangle {
                radius: 12.5
                color: "#2e2e2e"
                border.color: "grey"
                border.width: bw
                opacity: 1
                Rectangle {
                    width: parent.radius
                    anchors.rightMargin: drawerMainList.width - parent.radius
                    color: parent.color
                }
            }

            Component {
                id: sectionHeading
                Rectangle {
                    height: 28
                    color: "transparent"

                    required property string section

                    Text {
                        text: section
                        color: "white"
                        font.pixelSize: 14
                    }
                }
            }
            ColumnLayout {
                anchors.fill: parent
                ListView {
                    id: drawerList

                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Layout.topMargin: 25
                    Layout.leftMargin: 10
                    Layout.rightMargin: 10

                    clip: true
                    spacing: 4

                    model: ListModel {
                        ListElement {
                            name: "Standart"
                            icosource: "qrc:/icons/icon_calculator.png"
                            page: "qrc:/qalculator/app/qml/page/Standart.qml"
                            section: "Calculator"
                        }
                        ListElement {
                            name: "Angle"
                            icosource: "qrc:/icons/icon_angle.png"
                            page: "qrc:/qalculator/app/qml/page/Converter.qml"
                            section: "Converter"
                        }
                        ListElement {
                            name: "Data"
                            icosource: "qrc:/icons/icon_data.png"
                            page: "qrc:/qalculator/app/qml/page/Converter.qml"
                            section: "Converter"
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
                            appIco.source = icosource;

                            if (section == "Calculator")
                                historyButton.visible = true;
                            else
                                historyButton.visible = false;

                            if (section == "Converter")
                                Converter.currentConverter = name;

                            stackView.pop();
                            stackView.push(page);
                            calcType.text = name;
                        }
                    }

                    section.property: "section"
                    section.criteria: ViewSection.FullString
                    section.delegate: sectionHeading
                }

                StyledToolButton {
                    id: settingsButton

                    iconSource: "qrc:/icons/icon_settings.png"

                    textButton: "Settings"
                    textBold: false

                    contentSpacing: 5
                    imageLeftMargin: 5
                    textItemAlign: Qt.AlignLeft

                    Layout.fillWidth: true
                    Layout.margins: 10
                    Layout.minimumHeight: 40
                    Layout.maximumHeight: 40

                    onClicked: {
                        drawerMainList.close();
                        settingsDialog.open();
                    }
                }
            }
        }
        Drawer {
            id: drawerHistory
            width: window.width
            height: 310 - bw
            y: parent.y + bw
            modal: true
            interactive: true
            edge: Qt.BottomEdge
            background: Rectangle {
                radius: 12.5
                color: "#2e2e2e"
                border.color: "grey"
                border.width: bw
            }

            ListView {
                id: historyListView
                anchors.centerIn: parent
                width: 250
                height: parent.height - windowToolBar.height
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

    StyledDialog {
        id: settingsDialog
    }
}
