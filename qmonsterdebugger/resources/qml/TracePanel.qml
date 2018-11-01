import QtQuick 2.8
import QtQuick.Dialogs 1.3
import QtQuick.Layouts 1.4
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2 as Qml2
import QtQuick.Controls.Styles 1.4
import DeMonsters.Debug 1.0

Item {
    Dialog {
        id: msgDlg
        modality: Qt.WindowModal
        title: "Message"

        contentItem: Rectangle {
            color: "lightskyblue"
            implicitWidth: 800
            implicitHeight: 600
            TextArea {
                anchors.fill: parent
                id: textArea
            }
        }
    }

//    anchors.fill: parent
    property alias model: tableView.model
    TableView {
        id: tableView

    //    property var sizes: ({})
        TableViewColumn { id: line; role: "Line"; title: "#"; width: 40; movable: false }
        TableViewColumn { id: time; role: "Time"; title: "Time"; width: 100; movable: false }
        TableViewColumn { id: target; role: "Target"; title: "Target"; width: 170; movable: false }
        TableViewColumn { id: message; role: "Message"; title: "Message"; width: parent.width - 400; movable: false }
        TableViewColumn { id: memory; role: "Memory"; title: "Memory"; width: 90; movable: false }

        anchors.top: parent.top
        anchors.bottom: clearBtn.top
        width: parent.width

        onRowCountChanged: {
            if (autoSwitch.checked) {
                tableView.positionViewAtRow(rowCount - 1, ListView.Contain)
            }
        }

        onDoubleClicked: {
            textArea.text = model.data(model.index(row, row), TraceItem.Message)
            msgDlg.open()
        }

        style: TableViewStyle {
            property var __syspal: SystemPalette {
                colorGroup: tableView.enabled ?
                                SystemPalette.Active : SystemPalette.Disabled
            }

            backgroundColor: "#e3ecf4"
            alternateBackgroundColor: "#fff"
            textColor: "#000"


            itemDelegate: Item {
                id: itemDel
                height: Math.max(30, label.implicitHeight * 1.2)
                readonly property int modelRow: styleData.row ? styleData.row : 0
                readonly property int modelCol: styleData.column ? styleData.column : 0
                property int implicitWidth: label.implicitWidth + 20

                Text {
                    id: label
                    objectName: "label"
                    width: parent.width
                    anchors.leftMargin: 12
                    anchors.left: parent.left
                    anchors.right: parent.right
                    horizontalAlignment: styleData.textAlignment
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.verticalCenterOffset: 1
                    elide: styleData.elideMode
                    text: styleData.value !== undefined ? styleData.value.toString() : ""
                    color: styleData.textColor
                    renderType: Text.NativeRendering
    //                wrapMode: Text.WordWrap
                }

    //            Component.onCompleted: {
    //                if (styleData.role === "Message") {
    //                    var item = sizes[modelRow]
    //                    item.height = Qt.binding(function() { return itemDel.height })
    //                }
    //            }
            }

            rowDelegate: Rectangle {
                id: rowDel
                height: 30
                property color selectedColor: styleData.hasActiveFocus ? "#38d" : "#999"
                readonly property int modelRow: styleData.row ? styleData.row : 0
                gradient: Gradient {
                    GradientStop {
                        color: styleData.selected ? Qt.lighter(selectedColor, 1.3) :
                                                    styleData.alternate ? alternateBackgroundColor : backgroundColor
                        position: 0
                    }
                    GradientStop {
                        color: styleData.selected ? Qt.lighter(selectedColor, 1.0) :
                                                    styleData.alternate ? alternateBackgroundColor : backgroundColor
                        position: 1
                    }
                }
                Rectangle {
                    anchors.bottom: parent.bottom
                    width: parent.width
                    height: 1
                    color: styleData.selected ? Qt.darker(selectedColor, 1.4) : "transparent"
                }
                Rectangle {
                    anchors.top: parent.top
                    width: parent.width ; height: 1
                    color: styleData.selected ? Qt.darker(selectedColor, 1.1) : "transparent"
                }

    //            Component.onCompleted: {
    //                sizes[modelRow] = this
    //            }
            }
        }
    }
        Switch {
            id: autoSwitch
            anchors.bottom: parent.bottom
    //        text: qsTr("Auto Scroll")
            checked: true
        }
        Button {
            id: clearBtn
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            text: "Clear traces"
            onClicked: model.clear()
        }
}

