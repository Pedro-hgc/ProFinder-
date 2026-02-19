// ui/TelaBusca.qml

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: buscaPage

    function atualizarLista(termo = "") {
        let resultados = gerenciador.buscarFornecedores(termo);
        listaModelo.clear();
        for (let i = 0; i < resultados.length; i++) {
            listaModelo.append({"detalhe": resultados[i]});
        }
    }

    // --- NOVO: CONEXÃO REATIVA ---
    Connections {
        target: gerenciador
        // No Qt, sinais como 'dadosAlterados' tornam-se 'onDadosAlterados' no QML
        onFornecedorAdicionado: {
            console.log("Banco de dados atualizado! Atualizando lista...")
            atualizarLista(buscaInput.text);
        }
    }
    // -----------------------------

    Component.onCompleted: atualizarLista("")

    header: ToolBar {
        RowLayout {
            anchors.fill: parent
            anchors.leftMargin: 10
            anchors.rightMargin: 10

            Label {
                // Chama a nova função C++ sempre que a interface precisar atualizar
                text: "Total: " + gerenciador.quantidadeFornecedores
                font.bold: true
                color: "#666"
            }
        }

        Label {
            text: "Buscar Fornecedores"
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 10

        RowLayout {
            Layout.fillWidth: true
            TextField {
                id: buscaInput
                Layout.fillWidth: true
                placeholderText: "Digite o serviço ou nome"
                onTextChanged: atualizarLista(text) // Opcional: Busca em tempo real ao digitar
            }
            Button {
                text: "Buscar"
                onClicked: atualizarLista(buscaInput.text)
            }
        }

        ListView {
            id: listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            model: ListModel { id: listaModelo }
            delegate: ItemDelegate {
                width: listView.width
                text: detalhe
            }
            Label {
                anchors.centerIn: parent
                text: "Nenhum fornecedor encontrado."
                visible: listaModelo.count === 0
                color: "gray"
            }
        }
    }
}
