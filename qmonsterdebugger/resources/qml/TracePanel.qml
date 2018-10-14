import QtQuick 2.8
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

TableView {
//    model: traceModel
    TableViewColumn { id: line; role: "Line"; title: "#"; width: 40 }
    TableViewColumn { id: time; role: "Time"; title: "Time"; width: 100 }
    TableViewColumn { id: target; role: "Target"; title: "Target"; width: 170 }
    TableViewColumn { id: message; role: "Message"; title: "Message"; width: parent.width - 400 }
    TableViewColumn { id: memory; role: "Memory"; title: "Memory"; width: 90 }
}
