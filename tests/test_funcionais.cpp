#include <QtTest/QtTest>
#include "../include/GerenciadorUsuarios.h"

/**
 * @brief Classe de testes unitários e funcionais utilizando QTest.
 */
class TestesFuncionais : public QObject {
    Q_OBJECT

private slots:
    void testCadastroCliente() {
        GerenciadorUsuarios manager;
        bool res = manager.cadastrarCliente("João Silva", "joao@email.com");
        QVERIFY(res == true);
        QCOMPARE(manager.getQuantidadeUsuarios(), 1);

        // Teste de falha (nome vazio)
        res = manager.cadastrarCliente("", "vazio@email.com");
        QVERIFY(res == false);
    }

    void testCadastroEBuscaFornecedor() {
        GerenciadorUsuarios manager;
        manager.cadastrarFornecedor("Maria Souza", "maria@email.com", "Manutenção de Ar Condicionado");
        manager.cadastrarFornecedor("Carlos TI", "carlos@email.com", "Infraestrutura de Redes");
        manager.cadastrarCliente("Pedro", "pedro@email.com"); // Não deve aparecer na busca

        QStringList resultados = manager.buscarFornecedores("Redes");
        QCOMPARE(resultados.size(), 1);
        QVERIFY(resultados.at(0).contains("Carlos TI"));

        resultados = manager.buscarFornecedores("Manutenção");
        QCOMPARE(resultados.size(), 1);
        QVERIFY(resultados.at(0).contains("Maria Souza"));
    }
};

QTEST_MAIN(TestesFuncionais)
#include "test_funcionais.moc"
