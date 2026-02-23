#include <QtTest/QtTest>
#include <QVariantMap>
#include <QVariantList>
#include <QFile>
#include "../include/GerenciadorUsuarios.h"

/**
 * @brief Classe de testes unitários e funcionais utilizando QTest.
 */
class TestesFuncionais : public QObject {
    Q_OBJECT

private slots:
    void init() {
        // Clean up database file before each test
        QFile::remove("profinder_db.db");
    }

    void testCadastroCliente() {
        GerenciadorUsuarios manager;
        bool res = manager.cadastrarCliente("João Silva", "joao@email.com", "000.000.000-00", "01/01/2000", "foto.png");
        QVERIFY(res == true);
        QCOMPARE(manager.getQuantidadeUsuarios(), 1);

        // Teste de falha (nome vazio)
        res = manager.cadastrarCliente("", "vazio@email.com","","","");
        QVERIFY(res == false);
        
        // Teste de falha (email vazio)
        res = manager.cadastrarCliente("Nome", "","","","");
        QVERIFY(res == false);
    }

    void testCadastroFornecedorCompleto() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Encanador"] = 5;
        servicos["Eletricista"] = 3;
        
        QStringList fotos;
        fotos << "foto1.jpg" << "foto2.jpg" << "foto3.jpg";
        
        bool res = manager.cadastrarFornecedor(
            "João Fornecedor","joao@email.com",
            "123.456.789-00", "15/10/2000","foto.png","12.000.0001-01",
            "certificado.pdf", fotos,"Trabalho com qualidade e pontualidade",
             servicos);
        
        QVERIFY(res == true);
        QCOMPARE(manager.getQuantidadeFornecedores(), 1);
        QCOMPARE(manager.getQuantidadeUsuarios(), 1);
    }

    void testCadastroFornecedorValidacaoCamposObrigatorios() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Encanador"] = 5;
        QStringList fotos;
        fotos << "foto1.jpg";
        
        // Teste: nome vazio
        bool res = manager.cadastrarFornecedor(
            "",
            "joao@email.com",
            "123.456.789-00",
            "15/10/2000",
            "perfil.jpg",
            "12.000.0001-01",
            "certificado.pdf",
            fotos,
            "Trabalho com qualidade",
            servicos
            );
        QVERIFY(res == false);
        
        // Teste: email vazio
        res = manager.cadastrarFornecedor(
            "João Fornecedor",
            "",
            "123.456.789-00",
            "15/10/2000",
            "perfil.jpg",
            "12.000.0001-01",
            "certificado.pdf",
            fotos,
            "Trabalho com qualidade",
            servicos
            );
        QVERIFY(res == false);
        
        // Teste: CPF/CNPJ vazio
        res = manager.cadastrarFornecedor(
            "João Fornecedor",
            "joao@email.com",
            "",
            "15/10/2000",
            "perfil.jpg",
            "12.000.0001-01",
            "certificado.pdf",
            fotos,
            "Trabalho com qualidade",
            servicos
            );
        QVERIFY(res == false);
        
        // Teste: certificado vazio
        res = manager.cadastrarFornecedor(
            "João Fornecedor",
            "joao@email.com",
            "123.456.789-00",
            "15/10/2000",
            "perfil.jpg",
            "12.000.0001-01",
            "",
            fotos,
            "Trabalho com qualidade",
            servicos
            );
        QVERIFY(res == false);
        
        // Teste: foto de perfil vazia
        res = manager.cadastrarFornecedor(
            "João Fornecedor",
            "joao@email.com",
            "123.456.789-00",
            "15/10/2000",
            "",
            "12.000.0001-01",
            "certificado.pdf",
            fotos,
            "Trabalho com qualidade",
            servicos
            );
        QVERIFY(res == false);
    }

    void testCadastroFornecedorValidacaoFotos() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Encanador"] = 5;
        
        // Teste: nenhuma foto (deve falhar)
        QStringList fotosVazias;
        bool res = manager.cadastrarFornecedor(
            "Nome",
            "email@test.com",
            "123.456.789-00",
            "15/10/2000",
            "perfil.jpg",
            "12.000.0001-01",
            "cert.pdf",
            fotosVazias,
            "Descricao",
            servicos
            );
        QVERIFY(res == false);
        
        // Teste: mais de 5 fotos (deve falhar)
        QStringList fotosMuitas;
        fotosMuitas << "foto1.jpg" << "foto2.jpg" << "foto3.jpg" 
                    << "foto4.jpg" << "foto5.jpg" << "foto6.jpg";
        res = manager.cadastrarFornecedor(
            "Nome",
            "email@test.com",
            "123.456.789-00",
            "01/01/2000",
            "perfil.jpg",
            "123456",
            "cert.pdf",
            fotosMuitas,
            "Descricao",
            servicos
            );
        QVERIFY(res == false);
        
        // Teste: exatamente 5 fotos (deve passar)
        QStringList fotos5;
        res = manager.cadastrarFornecedor(
            "Nome",
            "email@test.com",
            "123.456.789-00",
            "01/01/2000",
            "perfil.jpg",
            "12.345.678/0001-99",
            "certificado.pdf",
            fotos5,
            "Descricao do trabalho",
            servicos
            );
        QVERIFY(res == true);
    }

    void testCadastroFornecedorValidacaoServicos() {
        GerenciadorUsuarios manager;
        
        QStringList fotos;
        fotos << "foto1.jpg";
        
        // Teste: nenhum serviço (deve falhar)
        QVariantMap servicosVazios;
        bool res = manager.cadastrarFornecedor(
            "Nome",
            "email@test.com",
            "123.456.789-00",
            "01/01/2000",
            "perfil.jpg",
            "123456",
            "cert.pdf",
            fotos,
            "Descricao",
            servicosVazios
            );
        QVERIFY(res == false);
        
        // Teste: múltiplos serviços (deve passar)
        QVariantMap servicosMultiplos;
        servicosMultiplos["Encanador"] = 5;
        servicosMultiplos["Eletricista"] = 3;
        servicosMultiplos["Pintor"] = 7;

        res = manager.cadastrarFornecedor(
            "Nome",
            "email@test.com",
            "123.456.789-00",
            "01/01/2000",
            "perfil.jpg",
            "123456",
            "cert.pdf",
            fotos,
            "Descricao",
            servicosMultiplos
            );
        QVERIFY(res == true);
    }

    void testCadastroFornecedorDescricaoOpcional() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Encanador"] = 5;
        QStringList fotos;
        fotos << "foto1.jpg";
        
        // Teste: sem descrição (deve passar)
        bool res = manager.cadastrarFornecedor(
            "Nome",
            "email@test.com",
            "123.456.789-00",
            "01/01/2000",
            "perfil.jpg",
            "123456",
            "cert.pdf",
            fotos,
            "",
            servicos
            );
        QVERIFY(res == true);
        
        // Teste: com descrição (deve passar)
        res = manager.cadastrarFornecedor(
            "Nome2",
            "email2@test.com",
            "987.654.321-00",
            "02/02/1990",
            "perfil2.jpg",
            "654321",
            "cert2.pdf",
            fotos,
            "Trabalho com qualidade",
            servicos
            );
        QVERIFY(res == true);
    }

    void testBuscaFornecedoresPorNome() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Encanador"] = 5;
        QStringList fotos;
        fotos << "foto1.jpg";
        
        manager.cadastrarFornecedor(
            "Maria Souza",
            "maria@email.com",
            "123.456.789-00",
            "01/01/1990",
            "perfil.jpg",
            "12345678",
            "cert.pdf",
            fotos,
            "Descricao",
            servicos
            );

        
        QStringList resultados = manager.buscarFornecedores("Maria");
        QCOMPARE(resultados.size(), 1);
        QVERIFY(resultados.at(0).contains("Maria Souza"));
    }

    void testBuscaFornecedoresPorEmail() {
        GerenciadorUsuarios manager;

        QVariantMap servicos;
        servicos["Eletricista"] = 3;
        QStringList fotos;
        fotos << "foto1.jpg";

        manager.cadastrarFornecedor(
            "Carlos Silva",
            "carlos@email.com",
            "987.654.321-00",
            "01/01/1985",
            "perfil.jpg",
            "65432100",
            "cert.pdf",
            fotos,
            "Descricao",
            servicos
            );
        QStringList resultados = manager.buscarFornecedores("carlos@email.com");
        QCOMPARE(resultados.size(), 1);
        QVERIFY(resultados.at(0).contains("Carlos Silva"));
    }

    void testBuscaFornecedoresPorCPFCNPJ() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Pintor"] = 7;
        QStringList fotos;
        fotos << "foto1.jpg";
        
        manager.cadastrarFornecedor(
            "Pedro Santos",
            "pedro@email.com",
            "111.222.333-44",
            "20/05/1995",
            "perfil.jpg",
            "99.888.777/0001-11",
            "cert.pdf",
            fotos,
            "Descricao do Pedro",
            servicos
            );
        QStringList resultados = manager.buscarFornecedores("111.222.333-44");
        QCOMPARE(resultados.size(), 1);
        QVERIFY(resultados.at(0).contains("Pedro Santos"));
        QVERIFY(resultados.at(0).contains("111.222.333-44"));
    }

    void testBuscaFornecedoresPorServico() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicosMaria;
        servicosMaria["Manutenção de Ar Condicionado"] = 5;
        
        QVariantMap servicosCarlos;
        servicosCarlos["Infraestrutura de Redes"] = 3;
        
        QStringList fotos;
        fotos << "foto1.jpg";
        
        manager.cadastrarFornecedor(
            "Maria Souza",
            "maria@email.com",
            "123.456.789-00",
            "10/05/1990",
            "perfil.jpg",
            "11.222.333/0001-00",
            "cert.pdf",
            fotos,
            "Especialista em Ar",
            servicosMaria
            );
        manager.cadastrarFornecedor(
            "Carlos TI",
            "carlos@email.com",
            "987.654.321-00",
            "15/08/1985",
            "perfil2.jpg",
            "44.555.666/0001-11",
            "cert2.pdf",
            fotos,
            "Infraestrutura completa",
            servicosCarlos
            );
        manager.cadastrarCliente("Pedro", "pedro@email.com", "111.222.333-44", "01/01/2000", "perfil.jpg");
        QStringList resultados = manager.buscarFornecedores("Redes");
        QCOMPARE(resultados.size(), 1);
        QVERIFY(resultados.at(0).contains("Carlos TI"));
        
        resultados = manager.buscarFornecedores("Manutenção");
        QCOMPARE(resultados.size(), 1);
        QVERIFY(resultados.at(0).contains("Maria Souza"));
    }

    void testBuscaFornecedoresVazia() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Encanador"] = 5;
        QStringList fotos;
        fotos << "foto1.jpg";
        
        manager.cadastrarFornecedor(
            "Fornecedor 1",
            "f1@email.com",
            "111.111.111-11",
            "01/01/1990",
            "perfil1.jpg",
            "111111110001",
            "cert1.pdf",
            fotos,
            "Descricao",
            servicos
            );
        manager.cadastrarFornecedor(
            "Fornecedor 2",
            "f2@email.com",
            "222.222.222-22",
            "02/02/1992",
            "perfil2.jpg",
            "222222220001",
            "cert2.pdf",
            fotos,
            "Descricao 2",
            servicos
            );
        manager.cadastrarCliente(
            "Cliente",
            "cliente@email.com",
            "000.000.000-00",
            "01/01/2000",
            "perfil_cliente.jpg"
            );
        QStringList resultados = manager.buscarFornecedores("");
        QCOMPARE(resultados.size(), 2);
    }

    void testBuscaFornecedoresComIndices() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Encanador"] = 5;
        QStringList fotos;
        fotos << "foto1.jpg";
        
        manager.cadastrarFornecedor(
            "Fornecedor 1",
            "f1@email.com",
            "111.111.111-11",
            "01/01/1990",
            "perfil1.jpg",
            "111111110001",
            "cert1.pdf",
            fotos,
            "Descricao 1",
            servicos
            );
        manager.cadastrarFornecedor(
            "Fornecedor 2",
            "f2@email.com",
            "222.222.222-22",
            "02/02/1992",
            "perfil2.jpg",
            "222222220002",
            "cert2.pdf",
            fotos,
            "Descricao 2",
            servicos
            );
        QVariantList resultados = manager.buscarFornecedoresComIndices("");
        QCOMPARE(resultados.size(), 2);
        
        QVERIFY(resultados.at(0).toMap().contains("index"));
        QVERIFY(resultados.at(0).toMap().contains("display"));
        QVERIFY(resultados.at(0).toMap().contains("nome"));
        QCOMPARE(resultados.at(0).toMap()["index"].toInt(), 0);
        QCOMPARE(resultados.at(1).toMap()["index"].toInt(), 1);
    }

    void testObterDetalhesFornecedor() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Encanador"] = 5;
        servicos["Eletricista"] = 3;
        
        QStringList fotos;
        fotos << "foto1.jpg" << "foto2.jpg";
        
        manager.cadastrarFornecedor(
            "João Fornecedor",
            "joao@email.com",
            "123.456.789-00",
            "01/01/1980",
            "perfil.jpg",
            "12.345.678/0001-99",
            "certificado.pdf",
            fotos,
            "Trabalho com qualidade",
            servicos
            );
        
        QVariantMap detalhes = manager.obterDetalhesFornecedor(0);
        
        QVERIFY(!detalhes.isEmpty());
        QCOMPARE(detalhes["nome"].toString(), QString("João Fornecedor"));
        QCOMPARE(detalhes["email"].toString(), QString("joao@email.com"));
        QCOMPARE(detalhes["cpfCnpj"].toString(), QString("123.456.789-00"));
        QCOMPARE(detalhes["certificadoAntecedentes"].toString(), QString("certificado.pdf"));
        QCOMPARE(detalhes["fotoPerfil"].toString(), QString("perfil.jpg"));
        QCOMPARE(detalhes["descricaoTrabalho"].toString(), QString("Trabalho com qualidade"));
        
        QStringList fotosRetornadas = detalhes["fotosServico"].toStringList();
        QCOMPARE(fotosRetornadas.size(), 2);
        QVERIFY(fotosRetornadas.contains("foto1.jpg"));
        QVERIFY(fotosRetornadas.contains("foto2.jpg"));
        
        QVariantMap servicosRetornados = detalhes["servicosComAnos"].toMap();
        QCOMPARE(servicosRetornados.size(), 2);
        QCOMPARE(servicosRetornados["Encanador"].toInt(), 5);
        QCOMPARE(servicosRetornados["Eletricista"].toInt(), 3);
    }

    void testGetIndiceFornecedor() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Encanador"] = 5;
        QStringList fotos;
        fotos << "foto1.jpg";
        
        manager.cadastrarFornecedor(
            "Fornecedor 1",
            "f1@email.com",
            "111.111.111-11",
            "01/01/1990",
            "perfil1.jpg",
            "111111110001",
            "cert1.pdf",
            fotos,
            "Descricao 1",
            servicos
            );
        manager.cadastrarFornecedor(
            "Fornecedor 2",
            "f2@email.com",
            "222.222.222-22",
            "02/02/1992",
            "perfil2.jpg",
            "222222220002",
            "cert2.pdf",
            fotos,
            "Descricao 2",
            servicos
            );
        int index1 = manager.getIndiceFornecedor("Fornecedor 1");
        int index2 = manager.getIndiceFornecedor("Fornecedor 2");
        int indexInexistente = manager.getIndiceFornecedor("Inexistente");
        
        QCOMPARE(index1, 0);
        QCOMPARE(index2, 1);
        QCOMPARE(indexInexistente, -1);
    }

    void testMultiplosServicosComAnos() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Encanador"] = 5;
        servicos["Eletricista"] = 3;
        servicos["Pintor"] = 7;
        servicos["Carpinteiro"] = 2;
        
        QStringList fotos;
        fotos << "foto1.jpg" << "foto2.jpg";
        
        manager.cadastrarFornecedor(
            "Fornecedor Completo",
            "completo@email.com",
            "123.456.789-00",
            "10/10/1980",
            "perfil.jpg",
            "12345678000199",
            "cert.pdf",
            fotos,
            "Ofereço múltiplos serviços",
            servicos
            );
        QVariantMap detalhes = manager.obterDetalhesFornecedor(0);
        QVariantMap servicosRetornados = detalhes["servicosComAnos"].toMap();
        
        QCOMPARE(servicosRetornados.size(), 4);
        QCOMPARE(servicosRetornados["Encanador"].toInt(), 5);
        QCOMPARE(servicosRetornados["Eletricista"].toInt(), 3);
        QCOMPARE(servicosRetornados["Pintor"].toInt(), 7);
        QCOMPARE(servicosRetornados["Carpinteiro"].toInt(), 2);
        
        // Verificar que aparece na busca por qualquer serviço
        QStringList resultados = manager.buscarFornecedores("Encanador");
        QCOMPARE(resultados.size(), 1);
        
        resultados = manager.buscarFornecedores("Pintor");
        QCOMPARE(resultados.size(), 1);
    }

    void testFormatoBuscaResumido() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Encanador"] = 5;
        servicos["Eletricista"] = 3;
        
        QStringList fotos;
        fotos << "foto1.jpg";
        
        manager.cadastrarFornecedor(
            "João Silva",
            "joao@email.com",
            "123.456.789-00",
            "01/01/1980",
            "perfil.jpg",
            "12345678000199",
            "cert.pdf",
            fotos,
            "Descrição",
            servicos
            );
        QStringList resultados = manager.buscarFornecedores("");
        QCOMPARE(resultados.size(), 1);
        
        QString resultado = resultados.at(0);
        // Verificar formato: Nome - Serviços (Email) - CPF/CNPJ
        QVERIFY(resultado.contains("João Silva"));
        QVERIFY(resultado.contains("Encanador"));
        QVERIFY(resultado.contains("Eletricista"));
        QVERIFY(resultado.contains("joao@email.com"));
        QVERIFY(resultado.contains("123.456.789-00"));
        // Verificar que não contém informações sensíveis além do CPF/CNPJ
        QVERIFY(!resultado.contains("cert.pdf"));
        QVERIFY(!resultado.contains("Descrição"));
    }

    void testQuantidadeFornecedores() {
        GerenciadorUsuarios manager;
        
        QVariantMap servicos;
        servicos["Encanador"] = 5;
        QStringList fotos;
        fotos << "foto1.jpg";
        
        QCOMPARE(manager.getQuantidadeFornecedores(), 0);
        
        manager.cadastrarFornecedor(
            "Fornecedor 1",
            "f1@email.com",
            "111.111.111-11",
            "01/01/1990",
            "perfil1.jpg",
            "111111110001",
            "cert1.pdf",
            fotos,
            "Descricao 1",
            servicos
            );

        QCOMPARE(manager.getQuantidadeFornecedores(), 1);
        manager.cadastrarFornecedor(
            "Fornecedor 2",
            "f2@email.com",
            "222.222.222-22",
            "02/02/1992",
            "perfil2.jpg",
            "222222220002",
            "cert2.pdf",
            fotos,
            "Descricao 2",
            servicos
            );
        QCOMPARE(manager.getQuantidadeFornecedores(), 2);
        
        manager.cadastrarCliente(
            "Cliente",
            "cliente@email.com",
            "000.000.000-00",
            "01/01/2000",
            "perfil_cliente.jpg"
            );
        QCOMPARE(manager.getQuantidadeFornecedores(), 2); // Não deve mudar
        QCOMPARE(manager.getQuantidadeUsuarios(), 3); // Total deve ser 3
    }
};

QTEST_MAIN(TestesFuncionais)
#include "test_funcionais.moc"
