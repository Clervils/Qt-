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
            //餐馆图标
            MapItemView {
                model: ListModel {
                    ListElement { name: "Point A"; latitude: 39.9917; longitude: 116.3055 }
                    ListElement { name: "Point B"; latitude: 39.995; longitude: 116.31 }
                    // 添加更多点的名称和坐标,通过经纬度定位（还需要在locationManager.cpp中添加信息
                }

                delegate: MapQuickItem {
                    coordinate: QtPositioning.coordinate(latitude, longitude)
                    anchorPoint.x: image.width / 2
                    anchorPoint.y: image.height

                    sourceItem: Image {
                        id: image
                        source: "qrc:/restaurant.png" // 使用自定义的标记图像
                        sourceSize.width: 20 // 设置图像宽度为20像素
                        sourceSize.height: 20 // 设置图像高度为20像素
                    }

                    property var infoWindow; // 将infoWindow声明为属性

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if (infoWindow) {
                                infoWindow.destroy(); // 销毁窗口
                                infoWindow = null; // 清空引用
                            } else {
                                // 获取被点击的地点信息
                                //交互方式：点击->位置坐标信息->地点名->通过locationManageer.cpp中的getLocationByName函数对应到某一特定location->获得location的其他信息
                                var loc = locationManager.getLocationByName(name);//loationManager在.cpp和.h文件中实现

                                // 访问位置属性
                                var locationName = loc["name"].toString();
                                var description = loc["description"].toString();
                                var category = loc["category"].toString();
                                var rating = loc["rating"].toString();

                                // 创建弹出窗口
                                infoWindow = Qt.createQmlObject(
                                    // QML 源字符串用于 infoWindow
                                    'import QtQuick 2.15; import QtQuick.Controls 2.15; import QtQuick.Layouts 1.3; Item { width: 200; height: 100; Rectangle { color: "white"; border.color: "black"; anchors.centerIn: parent; ColumnLayout { anchors.fill: parent; Text { text: "' + locationName + '" } Text { text: "Description: ' + description + '" } Text { text: "Category: ' + category + '" } Text { text: "Rating: ' + rating + '" } } } }',
                                    // infoWindow 的父对象
                                    map,
                                    // 存储 infoWindow 对象的变量名
                                    "infoWindow"
                                );

                                // 设置弹出窗口位置
                                if (infoWindow) {
                                    var point = map.fromCoordinate(QtPositioning.coordinate(latitude, longitude));
                                    infoWindow.x = point.x - infoWindow.width / 2 + 10;
                                    infoWindow.y = point.y - infoWindow.height - 5;
                                }
                            }
                        }
                    }
                }
            }
            //门图标
            MapItemView {
                model: ListModel {
                    ListElement { name: "东南门"; latitude: 39.98880918384113; longitude: 116.30965965926265 }
                    ListElement { name: "东门"; latitude: 39.99077617354559; longitude: 116.30950388042686 }
                    ListElement { name: "西门"; latitude:  39.99265519209038; longitude: 116.29849828684394 }
                    ListElement { name: "南门"; latitude: 39.98516361992511; longitude: 116.30556125566841 }
                    ListElement { name: "西南门"; latitude: 39.98646328742977; longitude: 116.29941325333175 }

                }

                delegate: MapQuickItem {
                    coordinate: QtPositioning.coordinate(latitude, longitude)
                    anchorPoint.x: image2.width / 2
                    anchorPoint.y: image2.height

                    sourceItem: Image {
                        id: image2
                        source: "qrc:/door.png" // 使用自定义的标记图像
                        sourceSize.width: 20 // 设置图像宽度为20像素
                        sourceSize.height: 20 // 设置图像高度为20像素
                    }
                }
            }
        }


        //指南针
        Image {
                    id: compassImage
                    source: "qrc:/COMPASS.png" // 指南针图像
                    width: 50
                    height: 50
                    anchors {
                        top: parent.top
                        right: parent.right
                        topMargin: 10
                        rightMargin: 10
                    }
                    transform: Rotation {
                        origin.x: compassImage.width / 2
                        origin.y: compassImage.height / 2
                        angle: -map.bearing // 反转地图的旋转角度
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
              console.log("latitude=" + latitude + " longitude=" + longitude);
            }
        }
    }
}
