import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Item {
    width: 200; height: 100;
    Rectangle {
        color: "white"; border.color: "black";
        anchors.centerIn: parent;
        ColumnLayout {
            anchors.fill: parent;
            Text { text: arguments[0] } // 在此处访问 locationName
            Text { text: "描述: " + arguments[1] }
            Text { text: "类别: " + arguments[2] }
            Text { text: "评分: " + arguments[3] }
        }
    }
}
