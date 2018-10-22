import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

TableView {
    property var sizes: ({})
    TableViewColumn { id: line; role: "Line"; title: "#"; width: 40; movable: false }
    TableViewColumn { id: time; role: "Time"; title: "Time"; width: 100; movable: false }
    TableViewColumn { id: target; role: "Target"; title: "Target"; width: 170; movable: false }
    TableViewColumn { id: message; role: "Message"; title: "Message"; width: parent.width - 400; movable: false }
    TableViewColumn { id: memory; role: "Memory"; title: "Memory"; width: 90; movable: false }

    anchors.fill: parent

    itemDelegate: Rectangle {
        id: itemDel
        height: txt.height
        readonly property int modelRow: styleData.row ? styleData.row : 0
        Text {
            id: txt
            width: parent.width
//            height: parent ? parent.height : 0
            anchors.centerIn: parent
            renderType: Text.NativeRendering
            color: styleData.textColor
            elide: styleData.elideMode
            text: styleData.value
            wrapMode: Text.WordWrap
        }
        onHeightChanged: {
//            console.log("ROW NAME" + parent ? parent.height : 0)
            var rect = sizes[modelRow]
            rect.height = itemDel.height;
        }


    }

    rowDelegate: Rectangle {
        id: rowDel
        height: parent ? parent.height : 0
        signal sizeChanged(Rectangle rect)
        SystemPalette {
            id: palette;
            colorGroup: SystemPalette.Active
        }
        color: {
            var baseColor = styleData.alternate ? palette.alternateBase : palette.base
            return styleData.selected ? palette.highlight : baseColor
        }

        readonly property int modelRow: styleData.row ? styleData.row : 0

        Component.onCompleted: {
//            sizeChanged(rowDel)
            sizes[modelRow] = rowDel
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("[!] log: " + sizes[modelRow]);
            }
        }
    }
}
