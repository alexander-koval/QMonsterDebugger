import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4


TableViewStyle {
        id: root

        /*! The \l TableView attached to this style. */
        readonly property TableView control: __control

        /*! The text color. */
        property color textColor: __syspal.text

        /*! The background color. */
        property color backgroundColor: __syspal.base

        /*! The alternate background color. */
        property color alternateBackgroundColor: Qt.darker(__syspal.base, 1.06)

        /*! The text highlight color, used within selections. */
        property color highlightedTextColor: "white"

        /*! Activates items on single click. */
        property bool activateItemOnSingleClick: false

        padding.top: control.headerVisible ? 0 : 1

        /*! \qmlproperty Component TableViewStyle::headerDelegate
        Delegate for header. This delegate is described in \l {TableView::headerDelegate}
        */
        property Component headerDelegate: Rectangle {
//            source: "images/header.png"
//            border.left: 4
            Text {
                anchors.fill: parent
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
                anchors.leftMargin: 12
                text: styleData.value
                elide: Text.ElideRight
                color: textColor
                renderType: Text.NativeRendering
            }
            Rectangle {
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 1
                width: 1
                color: "#ccc"
            }
        }

        /*! \qmlproperty Component TableViewStyle::rowDelegate
        Delegate for header. This delegate is described in \l {TableView::rowDelegate}
        */
        property Component rowDelegate: Rectangle {
            height: 20
            property color selectedColor: styleData.hasActiveFocus ? "#38d" : "#999"
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
        }

        /*! \qmlproperty Component TableViewStyle::itemDelegate
        Delegate for item. This delegate is described in \l {TableView::itemDelegate}
        */
        property Component itemDelegate: Item {
            height: Math.max(16, label.implicitHeight)
            property int implicitWidth: sizehint.paintedWidth + 20

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
                text: styleData.value !== undefined ? styleData.value : ""
                color: styleData.textColor
                renderType: Text.NativeRendering
            }
            Text {
                id: sizehint
                font: label.font
                text: styleData.value ? styleData.value : ""
                visible: false
            }
        }
    }
