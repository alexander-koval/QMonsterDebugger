import QtQuick 2.8
import QtQuick.Window 2.4
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.4
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

//    header: TabBar {
//        id: bar
////            width: parent.width
//        TabButton {
//            width: Math.max(150, implicitWidth * 1.5)
//            text: qsTr("Home");
//        }
//        Repeater {
//            model: sessions
//            delegate: TabButton {
//                width: Math.max(150, implicitWidth * 1.5)
//                text: session ? session.title : ""
//            }

//            onItemAdded: {
//                bar.currentIndex = index + 1
//            }
//        }
//    }

//    StackLayout {
//        id: viewStack
//        width: parent.width
//        anchors.top: bar.bottom
//        anchors.bottom: parent.bottom
//        currentIndex: bar.currentIndex

//        Rectangle {
//            color: "lightblue"
//        }

//        Repeater {
//            model: sessions
//            delegate: Loader {
//                id: loader
//                sourceComponent: TracePanel { model: session ? session.traces : "" }
//            }
//        }
//    }


        TabView {
            id: tabView
            anchors.fill: parent

            Connections {
                target: sessions
                onDataChanged: {
                    tabView.currentIndex = topLeft.row + 1
                }
            }

            Repeater {
                model: sessions
                delegate: Tab {
                    title: session ? session.title : ""
                    width: Math.max(150, implicitWidth * 1.5)

                    sourceComponent: SplitView {
                        anchors.fill: parent
                        orientation: Qt.Vertical
                        ScrollView {
                            id: scrollView
                            height: 200
                            MemoryView {
                                id: memoryPanel
                                height: 200
                                width: 5000
                                monitor: session ? session.monitors : ""
                            }
                        }

                        TracePanel {
                            id: tracePanel
                            Layout.minimumHeight: 50
                            Layout.fillHeight: true
                            model: session ? session.traces : ""
                        }
                    }

                }
            }

            Tab {
                title: "Home"
                Rectangle { color: "lightblue" }
            }
        }
}
