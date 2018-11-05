import QtQuick 2.8
import QtCharts 2.2

ChartView {
    id: monitorChart
    antialiasing: true
    ValueAxis {
        id: yAxis
        min: 0
        max: 100
    }

//    ValueAxis {
//        id: xAxis
//    }

    DateTimeAxis {
        id: xAxis
//        min: new Date()
//        tickCount: 2
        format: "hh:mm:ss"
    }

    property var monitor:MonitorModel
    property int timer: 0

    Connections {
        target: monitor

        onDataChanged: {
            var memory = monitor.data(topLeft, 257) / 1024 / 1024;
            var date = new Date()
            yAxis.min = monitor.minMemory / 1024 / 1024;
            yAxis.max = Math.round(memory / 1000) * 1000;
            monitorSeries.append(date, memory)
            console.log("DATA_CHANED", memory, toMsecsSinceEpoch(date))
        }
    }

    LineSeries {
        id: monitorSeries
        name: "Memory"
        axisX: xAxis
        axisY: yAxis
    }

    Component.onCompleted: {
        var date = new Date()
        xAxis.min = date
        var newDate = new Date(date.getFullYear(), date.getMonth(), date.getDay(), date.getHours(), date.getMinutes() + 10, date.getSeconds(), date.getMilliseconds())
        xAxis.max = newDate
    }

    function toMsecsSinceEpoch(date) {
        var msecs = date.getTime();
        return msecs;
    }
}
