# 寻味燕园周边导航应用

这个应用是一个基于 Qt 框架和 Qt Location 模块开发的简单导航应用，旨在帮助用户在寻味燕园周边找到特定地点，并提供相关信息，比如地点描述、类别、评分以及距离周围各个门的距离等。

## 如何使用

1. **编译和运行**

   在使用此应用之前，请确保您的开发环境已经配置好了 Qt 开发环境，并且具备编译和运行 Qt Quick 应用的能力。使用 `qmake` 和 `make` 或者 Qt Creator 等工具来编译项目，然后运行生成的可执行文件即可。

2. **应用界面**

   应用启动后，您会看到一个地图界面，地图上标记了一些特定地点和各个门的位置。您可以在地图上点击标记的地点图标，查看该地点的详细信息，比如名称、描述、类别、评分以及距离各个门的距离。
   应用目前还在左上角位置添加了索引，完成按类根据不同标准进行排行的功能。

## 文件结构

- **MainWindow.qml**: 主界面的 QML 文件，包含地图显示、地点标记和相关交互功能的实现。
  - **地图显示和交互功能**
    - `Plugin`: 导入地图插件，用于显示地图。
    - `Map`: 显示地图，并设置地图中心点和缩放级别。
    - `PinchHandler`: 处理地图的捏放缩放手势，支持手势放大缩小地图。
    - `WheelHandler`: 处理地图的鼠标滚轮放大缩小手势。
    - `DragHandler`: 处理地图的拖拽手势，支持拖拽地图移动视角。
    - `Shortcut`: 快捷键控制地图放大缩小功能。
  - **索引功能与交互**
    - `MapItemView`: 标记特索引点的图标，用于打开索引。
      - `delegate`: 索引图标的代理。
      - `MouseArea`: 处理地点图标的点击事件，并弹出索引详细窗口。
  			-  通过myInference进行交互，交互方式类似locationManager
  - **地点标记和交互**
    - `MapItemView`: 标记特定地点的图标，可以点击查看详细信息。～此处需要补充信息
      - `delegate`: 地点图标的代理，用于创建地点图标和处理点击事件。
      - `MouseArea`: 处理地点图标的点击事件，并弹出地点详细信息窗口。
  			-  与locationManager交互，交互方式见注释
         -  点击创建窗口，窗口具体实现分装在`InfoWindow.qml`文件中
  - **指南针**
    - `Image`: 显示指南针图标，并根据地图旋转角度进行旋转。
- **InfoWindow.qml**: 用于显示地点详细信息的弹出窗口的 QML 文件。
  - **地点详细信息显示**
    - `Rectangle`: 弹出窗口的背景。
    - `ColumnLayout`: 垂直布局，用于显示地点详细信息的各个属性。
      - `Text`: 显示地点名称、描述、类别、评分以及距离各个门的距离等信息。
- **main.cpp**: 应用程序的入口文件，负责创建 `LocationManager` 实例并加载主 QML 文件。
- **LocationManager.h** 和 **LocationManager.cpp**: 定义了 `LocationManager` 类，用于管理地点信息。
  - `addLocation(const QString &name, qreal latitude, qreal longitude, const QString &description, const QString &category, int rating)`: 添加地点信息的函数。～此处需要补充信息
  - `getAllLocations()`: 获取所有地点信息的函数。
  - `getLocationByName(const QString &name)`: 根据名称获取地点信息的函数。
- **Inference.h** 和 **Inference.cpp**: 定义了 `Inference` 类，用于显示索引。
  - `showInference`: 创建Indexes对象并显示。
- **Indexes.h** 和 **Indexes.cpp**: 定义了 `Indexes` 类，用于实现按照分数距离分类排行索引。
  - `initializeData`: 初始化排名 ～此处需要补充信息，完成与LocationManager的交互，实现排名
  - `updateRank`: 更新排名
## 目前未实现功能
   - 用户评价·
   - （最短路径）


该项目基于 [MIT 许可证](https://opensource.org/licenses/MIT) 开放源代码。

