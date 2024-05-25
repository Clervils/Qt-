//MainWindow.qml

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15
import com.example



ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("寻味燕园周边")

    Rectangle {
        width: parent.width
        height: parent.height

        Plugin {
            id: mapPlugin
            name: "osm"
        }

        Map {
            id: map
            anchors.fill: parent
            plugin: mapPlugin
            center: QtPositioning.coordinate(39.9917, 116.3055)
            zoomLevel: 14

            PinchHandler {
                id: pinch
                target: null
                onActiveChanged: if (active) {
                    map.startCentroid = map.toCoordinate(pinch.centroid.position, false)
                }
                onScaleChanged: (delta) => {
                    map.zoomLevel += Math.log2(delta)
                    map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
                }
                onRotationChanged: (delta) => {
                    map.bearing -= delta
                    map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
                }
                grabPermissions: PointerHandler.TakeOverForbidden
            }

            WheelHandler {
                id: wheel
                acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                                 ? PointerDevice.Mouse | PointerDevice.TouchPad
                                 : PointerDevice.Mouse
                rotationScale: 1/120
                property: "zoomLevel"
            }

            DragHandler {
                id: drag
                target: null
                onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
            }

            Shortcut {
                enabled: map.zoomLevel < map.maximumZoomLevel
                sequence: StandardKey.ZoomIn
                onActivated: map.zoomLevel = Math.round(map.zoomLevel + 1)
            }
            Shortcut {
                enabled: map.zoomLevel > map.minimumZoomLevel
                sequence: StandardKey.ZoomOut
                onActivated: map.zoomLevel = Math.round(map.zoomLevel - 1)
            }

            MapItemView {
                        model: ListModel {
                            ListElement { name: "Point A"; latitude: 39.9917; longitude: 116.3055 }
                            ListElement { name: "Point B"; latitude: 39.995; longitude: 116.31 }
                            // 添加更多点的名称和坐标
                        }

                        delegate: MapQuickItem {
                            coordinate: QtPositioning.coordinate(model.latitude, model.longitude)
                            anchorPoint.x: image.width / 2
                            anchorPoint.y: image.height

                            sourceItem: Image {
                                id: image
                                source: "qrc:/restaurant.png" // 使用自定义的标记图像
                                sourceSize.width: 20 // 设置图像宽度为20像素
                                sourceSize.height: 20 // 设置图像高度为20像素
                            }

                            MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                                // 获取被点击的地点信息
                                                console.log("Clicked model:", model.name);
                                                var loc = locationManager.getLocationByName(model.name);

                                                // 访问位置属性
                                                var locationName = loc["name"].toString();
                                                var description = loc["description"].toString();
                                                var category = loc["category"].toString();
                                                var rating = loc["rating"].toString();

                                                // 创建弹出窗口
                                                var infoWindow = Qt.createQmlObject(
                                                    'import QtQuick 2.15; import QtQuick.Controls 2.15; import QtQuick.Layouts 1.3; Item { width: 200; height: 100; Rectangle { color: "white"; border.color: "black"; anchors.centerIn: parent; ColumnLayout { anchors.fill: parent; Text { text: "' + locationName + '" } Text { text: "Description: ' + description + '" } Text { text: "Category: ' + category + '" } Text { text: "Rating: ' + rating + '" } } } }',
                                                    map,
                                                    "infoWindow"
                                                );

                                                // 设置弹出窗口位置
                                                if (infoWindow) {
                                                    infoWindow.x = (map.width - infoWindow.width) / 2;
                                                    infoWindow.y = (map.height - infoWindow.height) / 2;
                                                }
                                }
                            }
                        }
            }


        }


        MapCircle {
            id: circle
            center: QtPositioning.coordinate(39.9917, 116.3055)
            radius: 50
            border.width: 5

            MouseArea {
                anchors.fill: parent
                drag.target: parent
            }
        }

        Control {
            id: labelcpp
            objectName: 'labelcpp'
            font.pointSize: 38
            property real latitudeSave: 39.9917
            property real longitudeSave: 116.3055

            function getText() {
                return map.center + " zoom " + map.zoomLevel.toFixed(3)
                        + " min " + map.minimumZoomLevel + " max " + map.maximumZoomLevel
            }

            function setCoordinate(latitude, longitude) {
              latitudeSave = latitude
              longitudeSave = longitude
              var newCenter = QtPositioning.coordinate(latitude, longitude)
              map.center = newCenter
              console.log("latitude=" + latitude + " longitude=" + longitude);
            }

        }
    }

}
