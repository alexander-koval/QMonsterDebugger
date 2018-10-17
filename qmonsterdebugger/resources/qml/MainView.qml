import QtQuick 2.8
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import DeMonsters.Debug 1.0

ApplicationWindow {
    visible: true
    width: 1200
    height: 800
    minimumWidth: 800
    minimumHeight: 600

    Component {
        id: trace
        TracePanel { id: tracePanel; anchors.fill: parent }
    }

    Connections {
//        target: mainMediator

//        onSessionCreated: {
//            tabView.addTab(title, trace)
//        }
    }

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

//    TabBar {
//        width: parent.width
//        TabButton {
//            text: "First"
//            width: implicitWidth
//        }
//        TabButton {
//            text: "Second"
//            width: implicitWidth
//        }
//        TabButton {
//            text: "Third"
//            width: implicitWidth
//        }
//    }

    TabView {
        id: tabView
        anchors.fill: parent
        Repeater {
            model: sessions
            delegate: Tab {
                title: session.title
                sourceComponent: TracePanel { model: session.traces }
            }
        }

        Tab {
            title: "Home"
            Rectangle { color: "green" }
        }


    }
}
