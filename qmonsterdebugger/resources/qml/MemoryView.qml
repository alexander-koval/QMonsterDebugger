import QtQuick 2.8
import QtCharts 2.2
import QtQuick.Controls 1.4

ChartView {
    property var monitor:MonitorModel
    property int timer: 0

    id: monitorChart
//    antialiasing: true

    ValueAxis {
        id: yAxis
        min: 0
        max: 100
    }

    DateTimeAxis {
        id: xAxis
        format: "hh:mm:ss"
        tickCount: 30

        min: new Date(Date.now())
        max: new Date(Date.now() + 1800000/*30min*/)
    }

    Connections {
        target: monitor

        onDataChanged: {
            var memory = monitor.data(topLeft, 257) / 1024 / 1024;
            var date = new Date()
            yAxis.max = Math.round(memory / 1000) * 1000;
            monitorSeries.append(date.getTime(), memory)
        }
    }

    LineSeries {
        id: monitorSeries
        name: "Memory"
        axisX: xAxis
        axisY: yAxis
    }

    Component.onCompleted: {
//        xAxis.visible = false
//            xAxis.max = 100
//            var date = new Date()
//            xAxis.min = date
//            var newDate = new Date(date.getFullYear(), date.getMonth(), date.getDay(), date.getHours(), date.getMinutes() + 10, date.getSeconds(), date.getMilliseconds())
//            xAxis.max = newDate
    }

    function toMsecsSinceEpoch(date) {
        var msecs = date.getTime();
        return msecs;
    }
}
