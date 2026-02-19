import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 360
    height: 640
    visible: true
    title: "App MVP"

    footer: TabBar {
        id: tabBar
        width: parent.width
        TabButton { text: "Cadastro" }
        TabButton { text: "Busca" }
    }

    StackLayout {
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        // Como os arquivos QML estão na mesma pasta,
        // o Qt os reconhece automaticamente como componentes.
        TelaCadastro {}
        TelaBusca {}
    }
}
