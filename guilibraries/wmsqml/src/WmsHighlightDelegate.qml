import QtQuick 2.2

//! [0]
// Define a highlight with customized movement between items.
Component {
    id: highlightBar
    Rectangle {
        width: parent.width;
        height: 30
        color: "lightsteelblue"
        y: parent.currentItem.y+5;
        Behavior on y { SpringAnimation { spring: 2; damping: 0.1 } }
    }
}
