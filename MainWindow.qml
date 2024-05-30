// MainWindow.qml

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 5.15
import QtPositioning 5.15
import com.example
import inference.example
import rating.example

ApplicationWindow {
    visible: true
    width: 1000
    height: 800
    title: qsTr("寻味燕园周边")

    // 计算两个地点之间的真实距离（单位：米）
    function calculateDistance(lat1, lon1, lat2, lon2) {
        // 将经纬度转换为 QtPositioning.coordinate 对象
        var coord1 = QtPositioning.coordinate(lat1, lon1);
        var coord2 = QtPositioning.coordinate(lat2, lon2);

        // 使用 distanceTo() 函数计算两个坐标之间的距离
        var distance = coord1.distanceTo(coord2);
        var roundedDistance = Math.round(distance);

           return roundedDistance;
    }

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
            //索引
            Image {
                    source: "search.png"
                    width: 40
                    height: 40
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.margins: 10
                    MouseArea {
                                anchors.fill: parent
                                onClicked: {
                                    myInference.showInference()
                                }
                            }
                }

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
                    //ListElement { name: "Point A"; latitude: 39.9917; longitude: 116.3055 }
                    //ListElement { name: "Point B"; latitude: 39.995; longitude: 116.31 }
                    //ListElement { name: "Point C"; latitude: 39.997862; longitude: 116.320524 }
                    ListElement{name:"子固路拌粉 中关村五号店"; latitude:39.988742; longitude:116.31992}
                    ListElement{name:"云佳瑶云南过桥米线"; latitude:39.982785; longitude:116.317141}
                    ListElement{name:"花小小新疆炒米粉"; latitude:39.997892; longitude:116.330636}
                    ListElement{name:"和府捞面"; latitude:39.984361; longitude:116.322492}
                    ListElement{name:"遇见小面"; latitude:39.984098; longitude:116.321836}
                    // 添加更多点的名称和坐标,通过经纬度定位（还需要在locationManager.cpp中添加信息
                }

                delegate: MapQuickItem {
                    coordinate: QtPositioning.coordinate(latitude, longitude)
                    anchorPoint.x: image.width / 2
                    anchorPoint.y: image.height

                    sourceItem: Image {
                            id:image
                            source: "noodles.png" // 使用自定义的标记图像
                            sourceSize.width: 30 // 设置图像宽度为20像素
                            sourceSize.height: 30 // 设置图像高度为20像素


                    }

                    property var infoWindow; // 将infoWindow声明为属性


                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            //再点击一次窗口消失
                            if (infoWindow) {
                                infoWindow.destroy(); // 销毁窗口
                                infoWindow = null; // 清空引用
                            } else {
                                // 获取被点击的地点信息
                                //交互方式：点击->位置坐标信息->地点名->通过locationManageer.cpp中的getLocationByName函数对应到某一特定location->获得location的其他信息
                                var loc = locationManager.getLocationByName(name);//loationManager在.cpp和.h文件中实现

                                var locationName = loc["name"].toString();
                                var description = loc["description"].toString();
                                var category = loc["category"].toString();
                                var rating = loc["rating"].toString();
                                var distance_to_EastDoor = calculateDistance(latitude, longitude, 39.99077617354559, 116.30950388042686).toString();
                                var distance_to_WestDoor = calculateDistance(latitude, longitude, 39.99265519209038, 116.29849828684394).toString();
                                var distance_to_SouthDoor = calculateDistance(latitude, longitude, 39.98516361992511, 116.30556125566841).toString();
                                var distance_to_SouthEastDoor = calculateDistance(latitude, longitude, 39.98880918384113, 116.30556125566841).toString();
                                var distance_to_SouthwestDoor = calculateDistance(latitude, longitude, 39.98646328742977, 116.29941325333175).toString();


                                // 创建弹出窗口
                                infoWindow = Qt.createComponent("qrc:/InfoMindow.qml").createObject(map);

                                // 设置InfoWindow的属性
                                infoWindow.locationName = locationName;
                                infoWindow.description = description;
                                infoWindow.category = category;
                                infoWindow.rating = rating;
                                infoWindow.distance_to_EastDoor = distance_to_EastDoor;
                                infoWindow.distance_to_WestDoor = distance_to_WestDoor;
                                infoWindow.distance_to_SouthDoor = distance_to_SouthDoor;
                                infoWindow.distance_to_SouthEastDoor = distance_to_SouthEastDoor;
                                infoWindow.distance_to_SouthWestDoor = distance_to_SouthwestDoor;


                                // 设置弹出窗口位置
                                var point = map.fromCoordinate(QtPositioning.coordinate(latitude, longitude));
                                infoWindow.x = point.x - infoWindow.width / 2 + 10;
                                infoWindow.y = point.y - infoWindow.height - 5;
                            }
                        }
                    }
                }
            }
            //餐馆图标
            MapItemView {
                model: ListModel {
                    ListElement{name:"吉野家"; latitude:39.988928; longitude:116.313634}
                    ListElement{name:"麦当劳"; latitude:39.98864; longitude:116.320018}
                    ListElement{name:"肯德基"; latitude:39.987907; longitude:116.320633}
                    ListElement{name:"德克士"; latitude:39.992251; longitude:116.31704}
                    ListElement{name:"华莱士"; latitude:39.991972; longitude:116.318333}

                    // 添加更多点的名称和坐标,通过经纬度定位（还需要在locationManager.cpp中添加信息
                }

                delegate: MapQuickItem {
                    coordinate: QtPositioning.coordinate(latitude, longitude)
                    anchorPoint.x: image1.width / 2
                    anchorPoint.y: image1.height

                    sourceItem: Image {
                            id:image1
                            source: "R-C.png" // 使用自定义的标记图像
                            sourceSize.width: 30 // 设置图像宽度为20像素
                            sourceSize.height: 30 // 设置图像高度为20像素


                    }

                    property var infoWindow; // 将infoWindow声明为属性


                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            //再点击一次窗口消失
                            if (infoWindow) {
                                infoWindow.destroy(); // 销毁窗口
                                infoWindow = null; // 清空引用
                            } else {
                                // 获取被点击的地点信息
                                //交互方式：点击->位置坐标信息->地点名->通过locationManageer.cpp中的getLocationByName函数对应到某一特定location->获得location的其他信息
                                var loc = locationManager.getLocationByName(name);//loationManager在.cpp和.h文件中实现

                                var locationName = loc["name"].toString();
                                var description = loc["description"].toString();
                                var category = loc["category"].toString();
                                var rating = loc["rating"].toString();
                                var distance_to_EastDoor = calculateDistance(latitude, longitude, 39.99077617354559, 116.30950388042686).toString();
                                var distance_to_WestDoor = calculateDistance(latitude, longitude, 39.99265519209038, 116.29849828684394).toString();
                                var distance_to_SouthDoor = calculateDistance(latitude, longitude, 39.98516361992511, 116.30556125566841).toString();
                                var distance_to_SouthEastDoor = calculateDistance(latitude, longitude, 39.98880918384113, 116.30556125566841).toString();
                                var distance_to_SouthwestDoor = calculateDistance(latitude, longitude, 39.98646328742977, 116.29941325333175).toString();


                                // 创建弹出窗口
                                infoWindow = Qt.createComponent("qrc:/InfoMindow.qml").createObject(map);

                                // 设置InfoWindow的属性
                                infoWindow.locationName = locationName;
                                infoWindow.description = description;
                                infoWindow.category = category;
                                infoWindow.rating = rating;
                                infoWindow.distance_to_EastDoor = distance_to_EastDoor;
                                infoWindow.distance_to_WestDoor = distance_to_WestDoor;
                                infoWindow.distance_to_SouthDoor = distance_to_SouthDoor;
                                infoWindow.distance_to_SouthEastDoor = distance_to_SouthEastDoor;
                                infoWindow.distance_to_SouthWestDoor = distance_to_SouthwestDoor;


                                // 设置弹出窗口位置
                                var point = map.fromCoordinate(QtPositioning.coordinate(latitude, longitude));
                                infoWindow.x = point.x - infoWindow.width / 2 + 10;
                                infoWindow.y = point.y - infoWindow.height - 5;
                            }
                        }
                    }
                }
            }
            //餐馆图标
            MapItemView {
                model: ListModel {
                    ListElement{name:"喜茶"; latitude:39.984402; longitude:116.322092}
                    ListElement{name:"沪上阿姨鲜果茶"; latitude:39.9921; longitude:116.323136}
                    ListElement{name:"霸王茶姬"; latitude:39.984355; longitude:116.32229}
                    ListElement{name:"茶百道"; latitude:39.98958; longitude:116.323669}
                    ListElement{name:"瑞幸咖啡"; latitude:39.990546; longitude:116.319749}
                    // 添加更多点的名称和坐标,通过经纬度定位（还需要在locationManager.cpp中添加信息
                }

                delegate: MapQuickItem {
                    coordinate: QtPositioning.coordinate(latitude, longitude)
                    anchorPoint.x: image2.width / 2
                    anchorPoint.y: image2.height

                    sourceItem: Image {
                            id:image2
                            source: "coffee.png" // 使用自定义的标记图像
                            sourceSize.width: 30 // 设置图像宽度为20像素
                            sourceSize.height: 30 // 设置图像高度为20像素


                    }

                    property var infoWindow; // 将infoWindow声明为属性


                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            //再点击一次窗口消失
                            if (infoWindow) {
                                infoWindow.destroy(); // 销毁窗口
                                infoWindow = null; // 清空引用
                            } else {
                                // 获取被点击的地点信息
                                //交互方式：点击->位置坐标信息->地点名->通过locationManageer.cpp中的getLocationByName函数对应到某一特定location->获得location的其他信息
                                var loc = locationManager.getLocationByName(name);//loationManager在.cpp和.h文件中实现

                                var locationName = loc["name"].toString();
                                var description = loc["description"].toString();
                                var category = loc["category"].toString();
                                var rating = loc["rating"].toString();
                                var distance_to_EastDoor = calculateDistance(latitude, longitude, 39.99077617354559, 116.30950388042686).toString();
                                var distance_to_WestDoor = calculateDistance(latitude, longitude, 39.99265519209038, 116.29849828684394).toString();
                                var distance_to_SouthDoor = calculateDistance(latitude, longitude, 39.98516361992511, 116.30556125566841).toString();
                                var distance_to_SouthEastDoor = calculateDistance(latitude, longitude, 39.98880918384113, 116.30556125566841).toString();
                                var distance_to_SouthwestDoor = calculateDistance(latitude, longitude, 39.98646328742977, 116.29941325333175).toString();


                                // 创建弹出窗口
                                infoWindow = Qt.createComponent("qrc:/InfoMindow.qml").createObject(map);

                                // 设置InfoWindow的属性
                                infoWindow.locationName = locationName;
                                infoWindow.description = description;
                                infoWindow.category = category;
                                infoWindow.rating = rating;
                                infoWindow.distance_to_EastDoor = distance_to_EastDoor;
                                infoWindow.distance_to_WestDoor = distance_to_WestDoor;
                                infoWindow.distance_to_SouthDoor = distance_to_SouthDoor;
                                infoWindow.distance_to_SouthEastDoor = distance_to_SouthEastDoor;
                                infoWindow.distance_to_SouthWestDoor = distance_to_SouthwestDoor;


                                // 设置弹出窗口位置
                                var point = map.fromCoordinate(QtPositioning.coordinate(latitude, longitude));
                                infoWindow.x = point.x - infoWindow.width / 2 + 10;
                                infoWindow.y = point.y - infoWindow.height - 5;
                            }
                        }
                    }
                }
            }
            //餐馆图标
            MapItemView {
                model: ListModel {

                    ListElement{name:"太太好粥"; latitude:39.989946; longitude:116.334342}
                    ListElement{name:"嘉和一品粥"; latitude:39.997862; longitude:116.330524}
                    ListElement{name:"一品生煎"; latitude:39.992457; longitude:116.323122}
                    ListElement{name:"曼玲粥店"; latitude:39.983065; longitude:116.324597}
                    ListElement{name:"神仙粥方潮汕砂锅粥"; latitude:39.992045; longitude:116.316963}
                    // 添加更多点的名称和坐标,通过经纬度定位（还需要在locationManager.cpp中添加信息
                }

                delegate: MapQuickItem {
                    coordinate: QtPositioning.coordinate(latitude, longitude)
                    anchorPoint.x: image3.width / 2
                    anchorPoint.y: image3.height

                    sourceItem: Image {
                            id:image3
                            source: "baozi.png" // 使用自定义的标记图像
                            sourceSize.width: 30 // 设置图像宽度为20像素
                            sourceSize.height: 30 // 设置图像高度为20像素


                    }

                    property var infoWindow; // 将infoWindow声明为属性


                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            //再点击一次窗口消失
                            if (infoWindow) {
                                infoWindow.destroy(); // 销毁窗口
                                infoWindow = null; // 清空引用
                            } else {
                                // 获取被点击的地点信息
                                //交互方式：点击->位置坐标信息->地点名->通过locationManageer.cpp中的getLocationByName函数对应到某一特定location->获得location的其他信息
                                var loc = locationManager.getLocationByName(name);//loationManager在.cpp和.h文件中实现

                                var locationName = loc["name"].toString();
                                var description = loc["description"].toString();
                                var category = loc["category"].toString();
                                var rating = loc["rating"].toString();
                                var distance_to_EastDoor = calculateDistance(latitude, longitude, 39.99077617354559, 116.30950388042686).toString();
                                var distance_to_WestDoor = calculateDistance(latitude, longitude, 39.99265519209038, 116.29849828684394).toString();
                                var distance_to_SouthDoor = calculateDistance(latitude, longitude, 39.98516361992511, 116.30556125566841).toString();
                                var distance_to_SouthEastDoor = calculateDistance(latitude, longitude, 39.98880918384113, 116.30556125566841).toString();
                                var distance_to_SouthwestDoor = calculateDistance(latitude, longitude, 39.98646328742977, 116.29941325333175).toString();


                                // 创建弹出窗口
                                infoWindow = Qt.createComponent("qrc:/InfoMindow.qml").createObject(map);

                                // 设置InfoWindow的属性
                                infoWindow.locationName = locationName;
                                infoWindow.description = description;
                                infoWindow.category = category;
                                infoWindow.rating = rating;
                                infoWindow.distance_to_EastDoor = distance_to_EastDoor;
                                infoWindow.distance_to_WestDoor = distance_to_WestDoor;
                                infoWindow.distance_to_SouthDoor = distance_to_SouthDoor;
                                infoWindow.distance_to_SouthEastDoor = distance_to_SouthEastDoor;
                                infoWindow.distance_to_SouthWestDoor = distance_to_SouthwestDoor;


                                // 设置弹出窗口位置
                                var point = map.fromCoordinate(QtPositioning.coordinate(latitude, longitude));
                                infoWindow.x = point.x - infoWindow.width / 2 + 10;
                                infoWindow.y = point.y - infoWindow.height - 5;
                            }
                        }
                    }
                }
            }
            //餐馆图标
            MapItemView {
                model: ListModel {

                    ListElement{name:"小吊梨汤"; latitude:39.99044; longitude:116.33321}
                    ListElement{name:"粤小年·顺德菜"; latitude:39.988634; longitude:116.319762}
                    ListElement{name:"锦府盐帮·李宅"; latitude:39.985264; longitude:116.320885}
                    ListElement{name:"汇贤府·李氏鲁菜"; latitude:39.976791; longitude:116.321839}
                    ListElement{name:"港丽餐厅"; latitude:39.98525; longitude:116.320653}
                    // 添加更多点的名称和坐标,通过经纬度定位（还需要在locationManager.cpp中添加信息
                }

                delegate: MapQuickItem {
                    coordinate: QtPositioning.coordinate(latitude, longitude)
                    anchorPoint.x: image4.width / 2
                    anchorPoint.y: image4.height

                    sourceItem: Image {
                            id:image4
                            source: "dd.png" // 使用自定义的标记图像
                            sourceSize.width: 30 // 设置图像宽度为20像素
                            sourceSize.height: 30 // 设置图像高度为20像素


                    }

                    property var infoWindow; // 将infoWindow声明为属性


                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            //再点击一次窗口消失
                            if (infoWindow) {
                                infoWindow.destroy(); // 销毁窗口
                                infoWindow = null; // 清空引用
                            } else {
                                // 获取被点击的地点信息
                                //交互方式：点击->位置坐标信息->地点名->通过locationManageer.cpp中的getLocationByName函数对应到某一特定location->获得location的其他信息
                                var loc = locationManager.getLocationByName(name);//loationManager在.cpp和.h文件中实现

                                var locationName = loc["name"].toString();
                                var description = loc["description"].toString();
                                var category = loc["category"].toString();
                                var rating = loc["rating"].toString();
                                var distance_to_EastDoor = calculateDistance(latitude, longitude, 39.99077617354559, 116.30950388042686).toString();
                                var distance_to_WestDoor = calculateDistance(latitude, longitude, 39.99265519209038, 116.29849828684394).toString();
                                var distance_to_SouthDoor = calculateDistance(latitude, longitude, 39.98516361992511, 116.30556125566841).toString();
                                var distance_to_SouthEastDoor = calculateDistance(latitude, longitude, 39.98880918384113, 116.30556125566841).toString();
                                var distance_to_SouthwestDoor = calculateDistance(latitude, longitude, 39.98646328742977, 116.29941325333175).toString();


                                // 创建弹出窗口
                                infoWindow = Qt.createComponent("qrc:/InfoMindow.qml").createObject(map);

                                // 设置InfoWindow的属性
                                infoWindow.locationName = locationName;
                                infoWindow.description = description;
                                infoWindow.category = category;
                                infoWindow.rating = rating;
                                infoWindow.distance_to_EastDoor = distance_to_EastDoor;
                                infoWindow.distance_to_WestDoor = distance_to_WestDoor;
                                infoWindow.distance_to_SouthDoor = distance_to_SouthDoor;
                                infoWindow.distance_to_SouthEastDoor = distance_to_SouthEastDoor;
                                infoWindow.distance_to_SouthWestDoor = distance_to_SouthwestDoor;


                                // 设置弹出窗口位置
                                var point = map.fromCoordinate(QtPositioning.coordinate(latitude, longitude));
                                infoWindow.x = point.x - infoWindow.width / 2 + 10;
                                infoWindow.y = point.y - infoWindow.height - 5;
                            }
                        }
                    }
                }
            }
            //餐馆图标
            MapItemView {
                model: ListModel {
                    ListElement{name:"海底捞火锅"; latitude:39.979867; longitude:116.300833}
                    ListElement{name:"呷哺呷哺"; latitude:39.984255; longitude:116.322646}
                    ListElement{name:"火炉火自助餐"; latitude:39.984307; longitude:116.321328}
                    ListElement{name:"翅客烧烤"; latitude:39.991883; longitude:116.316974}
                    ListElement{name:"巴奴毛肚火锅"; latitude:39.9842; longitude:116.322371}
                    // 添加更多点的名称和坐标,通过经纬度定位（还需要在locationManager.cpp中添加信息
                }

                delegate: MapQuickItem {
                    coordinate: QtPositioning.coordinate(latitude, longitude)
                    anchorPoint.x: image5.width / 2
                    anchorPoint.y: image5.height

                    sourceItem: Image {
                            id:image5
                            source: "hotpot.png" // 使用自定义的标记图像
                            sourceSize.width: 30 // 设置图像宽度为20像素
                            sourceSize.height: 30 // 设置图像高度为20像素


                    }

                    property var infoWindow; // 将infoWindow声明为属性


                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            //再点击一次窗口消失
                            if (infoWindow) {
                                infoWindow.destroy(); // 销毁窗口
                                infoWindow = null; // 清空引用
                            } else {
                                // 获取被点击的地点信息
                                //交互方式：点击->位置坐标信息->地点名->通过locationManageer.cpp中的getLocationByName函数对应到某一特定location->获得location的其他信息
                                var loc = locationManager.getLocationByName(name);//loationManager在.cpp和.h文件中实现

                                var locationName = loc["name"].toString();
                                var description = loc["description"].toString();
                                var category = loc["category"].toString();
                                var rating = loc["rating"].toString();
                                var distance_to_EastDoor = calculateDistance(latitude, longitude, 39.99077617354559, 116.30950388042686).toString();
                                var distance_to_WestDoor = calculateDistance(latitude, longitude, 39.99265519209038, 116.29849828684394).toString();
                                var distance_to_SouthDoor = calculateDistance(latitude, longitude, 39.98516361992511, 116.30556125566841).toString();
                                var distance_to_SouthEastDoor = calculateDistance(latitude, longitude, 39.98880918384113, 116.30556125566841).toString();
                                var distance_to_SouthwestDoor = calculateDistance(latitude, longitude, 39.98646328742977, 116.29941325333175).toString();


                                // 创建弹出窗口
                                infoWindow = Qt.createComponent("qrc:/InfoMindow.qml").createObject(map);

                                // 设置InfoWindow的属性
                                infoWindow.locationName = locationName;
                                infoWindow.description = description;
                                infoWindow.category = category;
                                infoWindow.rating = rating;
                                infoWindow.distance_to_EastDoor = distance_to_EastDoor;
                                infoWindow.distance_to_WestDoor = distance_to_WestDoor;
                                infoWindow.distance_to_SouthDoor = distance_to_SouthDoor;
                                infoWindow.distance_to_SouthEastDoor = distance_to_SouthEastDoor;
                                infoWindow.distance_to_SouthWestDoor = distance_to_SouthwestDoor;


                                // 设置弹出窗口位置
                                var point = map.fromCoordinate(QtPositioning.coordinate(latitude, longitude));
                                infoWindow.x = point.x - infoWindow.width / 2 + 10;
                                infoWindow.y = point.y - infoWindow.height - 5;
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
                    anchorPoint.x: image6.width / 2
                    anchorPoint.y: image6.height

                    sourceItem: Image {
                        id:image6
                        source: "Gate.png" // 使用自定义的标记图像
                        sourceSize.width: 20 // 设置图像宽度为20像素
                        sourceSize.height: 20 // 设置图像高度为20像素
                    }
                }
            }

        }


        //指南针
        Image {
                    id: compassImage
                    source: "south.png" // 指南针图像
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
