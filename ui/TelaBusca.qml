import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Page {
    id: buscaPage

    header: ToolBar {
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
            }
            Button {
                text: "Buscar"
                onClicked: {
                    let resultados = gerenciador.buscarFornecedores(buscaInput.text);
                    listaModelo.clear();
                    for (let i = 0; i < resultados.length; i++) {
                        listaModelo.append({"detalhe": resultados[i]});
                    }
                }
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
                text: "Nenhum resultado."
                visible: listaModelo.count === 0
                color: "gray"
            }
        }
    }
}
