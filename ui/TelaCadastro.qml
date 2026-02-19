import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: cadastroPage

    header: ToolBar {
        Label {
            text: "Novo Usuário"
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ColumnLayout {
        anchors.centerIn: parent
        width: parent.width * 0.8
        spacing: 15

        ComboBox {
            id: tipoCombo
            Layout.fillWidth: true
            model: ["Cliente", "Fornecedor"]
        }

        TextField {
            id: nomeInput
            Layout.fillWidth: true
            placeholderText: "Nome completo"
        }

        TextField {
            id: emailInput
            Layout.fillWidth: true
            placeholderText: "E-mail"
        }

        TextField {
            id: servicoInput
            Layout.fillWidth: true
            placeholderText: "Serviço oferecido"
            visible: tipoCombo.currentText === "Fornecedor"
        }

        Button {
            Layout.fillWidth: true
            text: "Cadastrar"
            onClicked: {
                let sucesso = false;
                if (tipoCombo.currentText === "Cliente") {
                    sucesso = gerenciador.cadastrarCliente(nomeInput.text, emailInput.text);
                } else {
                    sucesso = gerenciador.cadastrarFornecedor(nomeInput.text, emailInput.text, servicoInput.text);
                }

                if (sucesso) {
                    statusLabel.text = "Cadastrado com sucesso!";
                    statusLabel.color = "green";
                    nomeInput.text = ""; emailInput.text = ""; servicoInput.text = "";
                } else {
                    statusLabel.text = "Erro: Preencha os campos.";
                    statusLabel.color = "red";
                }
            }
        }

        Label {
            id: statusLabel
            Layout.alignment: Qt.AlignHCenter
            text: ""
        }
    }
}
