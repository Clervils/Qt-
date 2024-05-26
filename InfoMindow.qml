// InfoWindow.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Item {
    id: infoWindow
    width: 200
    height: 100

    property string locationName
    property string description
    property string category
    property string rating

    Rectangle {
        color: "white"
        border.color: "black"
        anchors.fill: parent
        anchors.margins: 10

        ColumnLayout {
            anchors.fill: parent
            spacing: 5
            Text { text: " " + infoWindow.locationName }
            Text { text: " 描述: " + infoWindow.description }
            Text { text: " 类别: " + infoWindow.category }
            Text { text: " 评分: " + infoWindow.rating }
        }
    }
}
