import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 1200
    height: 800
    minimumWidth: 800
    minimumHeight: 600

    menuBar: MenuBar {
        Menu {
            title: qsTr("&Edit")
            MenuItem {
                text: qsTr("&Edit")
                onTriggered: console.log("Open action triggered");
            }
        }
        Menu {
            title: "View"
            MenuItem {
                text: qsTr("View")
                onTriggered: Qt.quit();
            }
        }
        Menu {
            title: "Extra"
            MenuItem {
                text: qsTr("Extra")
                onTriggered: Qt.quit();
            }
        }
    }

//    TabView {
//           anchors.fill: parent
//           Repeater {
//               model: ["Foo", "Bar", "Baz"]
//               Tab {
//                   title: modelData
//               }
//           }
//       }
    TabView {
        anchors.fill: parent
        Tab {
            title: "Red"
            TracePanel { id: tracePanel; anchors.fill: parent }
        }
        Tab {
            title: "Blue"
            Rectangle { color: "blue" }
        }
        Tab {
            title: "Green"
            Rectangle { color: "green" }
        }
    }
}
