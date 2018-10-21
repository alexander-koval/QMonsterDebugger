import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

TableView {
    TableViewColumn { id: line; role: "Line"; title: "#"; width: 40; movable: false }
    TableViewColumn { id: time; role: "Time"; title: "Time"; width: 100; movable: false }
    TableViewColumn { id: target; role: "Target"; title: "Target"; width: 170; movable: false }
    TableViewColumn { id: message; role: "Message"; title: "Message"; width: parent.width - 400; movable: false }
    TableViewColumn { id: memory; role: "Memory"; title: "Memory"; width: 90; movable: false }

    highlightOnFocus: false

    rowDelegate: Rectangle {
        id: rowDel
//        color: "blue"
        height: text.height

        readonly property int modelRow: styleData.row ? styleData.row : 0

        MouseArea {
            anchors.fill: parent
//            onClicked: {
//                console.log("[!] log: " + modelRow);
//            }
        }
    }

    itemDelegate: Rectangle {
        id: itemDel
        width: parent.width
        height: text.height
        Text {
            id: text
            width: parent.width
            color: styleData.textColor
            elide: styleData.elideMode
            text: styleData.value
            wrapMode: Text.WordWrap
        }
    }
}
