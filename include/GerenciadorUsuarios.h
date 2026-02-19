// include/GerenciadorUsuarios.h

#ifndef GERENCIADORUSUARIOS_H
#define GERENCIADORUSUARIOS_H

#include <QObject>
#include <QVector>
#include <QStringList>
#include <QVariantMap>
#include <QVariantList>
#include "Usuario.h"

class GerenciadorUsuarios : public QObject {
    Q_OBJECT
    Q_PROPERTY(int quantidadeFornecedores READ getQuantidadeFornecedores NOTIFY fornecedorAdicionado);
private:
    QVector<Usuario*> m_usuarios;
    Usuario* m_usuarioLogado; // Currently logged in user
    const QString m_dbPath = "database.json";
    void salvarDados();
    void carregarDados();

public:
    explicit GerenciadorUsuarios(QObject *parent = nullptr);
    ~GerenciadorUsuarios();

    Q_INVOKABLE bool cadastrarCliente(const QString& nome, const QString& email, 
                                      const QString& cpf, const QString& dataNascimento, 
                                      const QString& fotoPerfil);
    Q_INVOKABLE bool cadastrarFornecedor(const QString& nome, const QString& email,
                                         const QString& cpf, const QString& dataNascimento, 
                                         const QString& fotoPerfil,
                                         const QString& cpfCnpj, const QString& certificadoAntecedentes,
                                         const QStringList& fotosServico, const QString& descricaoTrabalho,
                                         const QVariantMap& servicosComAnos);
    Q_INVOKABLE QVariantMap fazerLogin(const QString& email, const QString& cpf);
    Q_INVOKABLE QVariantMap obterDetalhesFornecedor(int index);
    Q_INVOKABLE int getIndiceFornecedor(const QString& nome);
    Q_INVOKABLE QVariantMap getUsuarioLogado();
    Q_INVOKABLE void fazerLogout();
  /**
     * @brief Retorna a quantidade total de usuários (Clientes e Fornecedores) no sistema.
     * Marcado como Q_INVOKABLE para ser acessível via QML.
     * @return Inteiro com o tamanho do vetor de usuários.
     */
    int getQuantidadeUsuarios() const;
    int getQuantidadeFornecedores() const;
    Q_INVOKABLE QStringList buscarFornecedores(const QString& termo);
    Q_INVOKABLE QVariantList buscarFornecedoresComIndices(const QString& termo);

signals:
    /**
     * @brief Sinal emitido sempre que o banco de dados JSON/Vetor é modificado.
     */
    void dadosAlterados();

    /**
     *@brief Sinal emitido sempre que o banco de dados tiver um novo Fornecedor Adicionado
     **/
     void fornecedorAdicionado();

    /**
     *@brief Sinal emitido sempre que o banco de dados tiver um novo Cliente Adicionado
     **/
     void clienteAdicionado();
};

#endif
