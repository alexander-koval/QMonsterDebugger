import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

TableView {
    id: tableView
    property var sizes: ({})
    TableViewColumn { id: line; role: "Line"; title: "#"; width: 40; movable: false }
    TableViewColumn { id: time; role: "Time"; title: "Time"; width: 100; movable: false }
    TableViewColumn { id: target; role: "Target"; title: "Target"; width: 170; movable: false }
    TableViewColumn { id: message; role: "Message"; title: "Message"; width: parent.width - 400; movable: false }
    TableViewColumn { id: memory; role: "Memory"; title: "Memory"; width: 90; movable: false }

    anchors.fill: parent

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
            height: Math.max(20, label.implicitHeight * 1.2)
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
                wrapMode: Text.WordWrap
            }

            Component.onCompleted: {
                if (styleData.role === "Message") {
                    var item = sizes[modelRow]
                    item.height = Qt.binding(function() { return itemDel.height })
                }
            }
        }

        rowDelegate: Rectangle {
            id: rowDel
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


            Component.onCompleted: {
                sizes[modelRow] = this
            }
        }
    }
}

