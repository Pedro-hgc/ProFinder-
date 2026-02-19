import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: telaInicial

    ColumnLayout {
        anchors.centerIn: parent
        width: parent.width * 0.8
        spacing: 30

        Label {
            text: "ProFinder"
            font.pixelSize: 36
            font.bold: true
            Layout.alignment: Qt.AlignHCenter
        }

        Button {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            text: "Login"
            font.pixelSize: 18
            onClicked: {
                stackView.push("TelaLogin.qml")
            }
        }

        Button {
            Layout.fillWidth: true
            Layout.preferredHeight: 50
            text: "Cadastro"
            font.pixelSize: 18
            onClicked: {
                stackView.push("TelaCadastro.qml")
            }
        }
    }
}
