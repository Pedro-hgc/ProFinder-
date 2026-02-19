import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 360
    height: 640
    visible: true
    title: "ProFinder"

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: TelaInicial {}
    }
}
