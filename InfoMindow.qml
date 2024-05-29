// InfoWindow.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import com.example
import rating.example

Item {
    id: infoWindow
    width: 280
    height: 340

    property string locationName
    property string description
    property string category
    property string rating
    property string distance_to_EastDoor
    property string distance_to_WestDoor
    property string distance_to_SouthDoor
    property string distance_to_SouthEastDoor
    property string distance_to_SouthWestDoor

    Rectangle {
        color: "white"
        border.color: "black"
        border.width:1
        radius: 10
        anchors.fill: parent
        anchors.margins: 10

        ColumnLayout {
            anchors.fill: parent
            spacing: 6
            Text {
                text: "  " + infoWindow.locationName
                font.bold: true
                font.pointSize: 16
            }
            RowLayout {
                spacing: 5
                Text {
                    text: "   描述: "
                    font.bold: true
                }
                Text {
                    text: infoWindow.description
                }
            }
            RowLayout {
                spacing: 5
                Text {
                    text: "   类别: "
                    font.bold: true
                }
                Text {
                    text: infoWindow.category
                }
            }
            RowLayout {
                spacing: 5
                Text {
                    text: "   评分: "
                    font.bold: true
                }
                Text {
                    text: infoWindow.rating
                }
                Button {
                        text: "我要评分"
                        onClicked: {
                            myratingbutton.showRating(infoWindow.locationName)
                            locationManager.updateRating(myratingbutton.ratingnum, infoWindow.locationName)
                        }
                        Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                }
            }
            Text {
                text: "  离各个门的距离"
                font.bold: true
                font.pointSize: 16
            }
            Text { text: "  离东门: " + infoWindow.distance_to_EastDoor + " m" }
            Text { text: "  离西门: " + infoWindow.distance_to_WestDoor + " m" }
            Text { text: "  离南门: " + infoWindow.distance_to_SouthDoor + " m"}
            Text { text: "  离东南门: " + infoWindow.distance_to_SouthEastDoor + " m" }
            Text { text: "  离西南门: " + infoWindow.distance_to_SouthWestDoor + " m" }
            Text { text: "  " }
        }

    }
    Connections {
            target: myratingbutton
            onRatingUpdated: {
                // 在评分更新后执行位置管理器的更新操作
                console.log(myratingbutton.ratingnum)
                locationManager.updateRating(myratingbutton.ratingnum, infoWindow.locationName)
            }
        }


}

