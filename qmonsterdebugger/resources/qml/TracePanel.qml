import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Rectangle {
    ListModel {
        id: listModel
        ListElement {
            name: "Bill Smith"
            number: "555 3264"
        }
        ListElement {
            name: "John Brown"
            number: "555 8426"
        }
        ListElement {
            name: "Sam Wise"
            number: "555 0473"
        }
    }

    TableView {
        width: parent.width
        height: parent.height
        TableViewColumn {
            role: "name"
            title: "Name"
            width: 100
        }
        TableViewColumn {
            role: "number"
            title: "Number"
            width: 200
        }
        model: traceModel
    }
//    GridView {
//        width: parent.width
//        height: parent.height

//        Component {
//            id: contactsDelegate
//            Rectangle {
//                width: parent.width
//                height: 40
//                color: "red"
//                Column {
//                    Text { text: '<b>Name:</b> ' + name }
//                    Text { text: '<b>Number:</b> ' + number }
//                }
//            }
//        }

//        model: listModel
//        delegate: contactsDelegate
//        focus: true
//    }
}
