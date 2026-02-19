// include/GerenciadorUsuarios.h

#ifndef GERENCIADORUSUARIOS_H
#define GERENCIADORUSUARIOS_H

#include <QObject>
#include <QVector>
#include <QStringList>
#include "Usuario.h"

class GerenciadorUsuarios : public QObject {
    Q_OBJECT
    Q_PROPERTY(int quantidadeFornecedores READ getQuantidadeFornecedores NOTIFY fornecedorAdicionado);
private:
    QVector<Usuario*> m_usuarios;
    const QString m_dbPath = "database.json";
    void salvarDados();
    void carregarDados();

public:
    explicit GerenciadorUsuarios(QObject *parent = nullptr);
    ~GerenciadorUsuarios();

    Q_INVOKABLE bool cadastrarCliente(const QString& nome, const QString& email);
    Q_INVOKABLE bool cadastrarFornecedor(const QString& nome, const QString& email, const QString& servico);
  /**
     * @brief Retorna a quantidade total de usuários (Clientes e Fornecedores) no sistema.
     * Marcado como Q_INVOKABLE para ser acessível via QML.
     * @return Inteiro com o tamanho do vetor de usuários.
     */
    int getQuantidadeUsuarios() const;
    int getQuantidadeFornecedores() const;
    Q_INVOKABLE QStringList buscarFornecedores(const QString& termo);

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
