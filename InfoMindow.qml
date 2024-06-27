// InfoWindow.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import com.example
import rating.example

Item {
    id: infoWindow
    width: 320
    height: 380

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
        id: container
        width: parent.width
        height: parent.height
        color: "#ffffff"  // 白色背景
        radius: 10
        border.color: "#d3d3d3"
        border.width: 3
        anchors.centerIn: parent
        anchors.margins: 10

        ColumnLayout {
            anchors.fill: parent
            spacing: 10
            anchors.topMargin: 15

            Rectangle {
                width: parent.width - 20
                height: 40
                radius: 5
                color: white
                border.color: "#77aa77"
                border.width: 2
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    text: infoWindow.locationName
                    font.bold: true
                    font.family: "Arial"
                    font.pointSize: 20
                    color: "#333333"
                    anchors.centerIn: parent
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }

            RowLayout {
                spacing: 5
                Text {
                    text: "  描述: "
                    font.bold: true
                    font.family: "Arial"
                    font.pointSize: 14
                    color: "#77aa77"
                }
                Text {
                    text: infoWindow.description
                    font.pointSize: 14
                    color: "#333333"
                }
            }

            RowLayout {
                spacing: 5
                Text {
                    text: "  类别: "
                    font.bold: true
                    font.family: "Arial"
                    font.pointSize: 14
                    color: "#77aa77"
                }
                Text {
                    text: infoWindow.category
                    font.pointSize: 14
                    color: "#333333"
                }
            }

            RowLayout {
                spacing: 5
                Text {
                    text: "  评分: "
                    font.bold: true
                    font.family: "Arial"
                    font.pointSize: 14
                    color: "#77aa77"
                }
                Text {
                    text: infoWindow.rating
                    font.pointSize: 14
                    color: "#333333"
                }
                Button {
                    text: "我要评分"
                    font.pointSize: 14
                    font.bold: true
                    background: Rectangle {
                        color: "#77aa77"  // 浅绿色按钮
                        radius: 5
                    }
                    contentItem: Text {
                        text: "我要评分"
                        font.bold: true
                        color: "white"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
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
                font.family: "Arial"
                font.pointSize: 16
                color: "#333333"
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter

            }

            Text {
                text: "   离东门  " + infoWindow.distance_to_EastDoor + " m"
                font.pointSize: 14
                color: "#333333"
            }
            Text {
                text: "   离西门  " + infoWindow.distance_to_WestDoor + " m"
                font.pointSize: 14
                color: "#333333"
            }
            Text {
                text: "   离南门  " + infoWindow.distance_to_SouthDoor + " m"
                font.pointSize: 14
                color: "#333333"
            }
            Text {
                text: "   离东南门 " + infoWindow.distance_to_SouthEastDoor + " m"
                font.pointSize: 14
                color: "#333333"
            }
            Text {
                text: "   离西南门  " + infoWindow.distance_to_SouthWestDoor + " m"
                font.pointSize: 14
                color: "#333333"
            }
            Text {
                text: "  "
            }
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
