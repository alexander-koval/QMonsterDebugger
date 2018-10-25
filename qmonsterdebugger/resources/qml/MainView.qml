import QtQuick 2.8
import QtQuick.Window 2.4
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.11
import DeMonsters.Debug 1.0

ApplicationWindow {
    visible: true
    width: 1200
    height: 800
    minimumWidth: 800
    minimumHeight: 600

//    Component {
//        id: trace
//        TracePanel { id: tracePanel; anchors.fill: parent }
//    }

//    Connections {
//        target: mainMediator

//        onSessionCreated: {
//            tabView.addTab(title, trace)
//        }
//    }

//    menuBar: MenuBar {
//        Menu {
//            title: qsTr("&Edit")
//            MenuItem {
//                text: qsTr("&Edit")
//                onTriggered: console.log("Open action triggered");
//            }
//        }
//        Menu {
//            title: "View"
//            MenuItem {
//                text: qsTr("View")
//                onTriggered: Qt.quit();
//            }
//        }
//        Menu {
//            title: "Extra"
//            MenuItem {
//                text: qsTr("Extra")
//                onTriggered: Qt.quit();
//            }
//        }
//    }

    Item {
        anchors.fill: parent

        Rectangle {
            anchors.fill: parent
            color: "lightblue"
        }

        TabBar {
            id: bar
            width: parent.width
            TabButton {
                width: Math.max(150, implicitWidth * 1.5)
                text: qsTr("Home");
            }
            Repeater {
                model: sessions
                delegate: TabButton {
                    width: Math.max(150, implicitWidth * 1.5)
                    text: session ? session.title : ""
                }
            }
        }

        Loader {
            id: viewer
            width: parent.width
            anchors.top: bar.bottom
            anchors.bottom: parent.bottom
        }

        StackLayout {
            id: viewStack
            width: parent.width
            anchors.top: bar.bottom
            anchors.bottom: parent.bottom
            currentIndex: bar.currentIndex

            Rectangle {
                color: "lightblue"
            }

            Repeater {
                model: sessions
                delegate: Loader {
                    id: loader
                    sourceComponent: TracePanel { model: session ? session.traces : "" }
                }
            }
        }


//        TabView {
//            id: tabView
//            anchors.fill: parent
//            Repeater {
//                model: sessions
//                delegate: Tab {
//                    title: session ? session.title : ""
//                    sourceComponent: TracePanel {
//                        model: session.traces
//                    }
//                }
//            }

//            Tab {
//                title: "Home"
//                Rectangle { color: "lightblue" }
//            }
//        }
    }
}
