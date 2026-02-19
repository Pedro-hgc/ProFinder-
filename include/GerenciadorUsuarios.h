#ifndef GERENCIADORUSUARIOS_H
#define GERENCIADORUSUARIOS_H

#include <QObject>
#include <QVector>
#include <QStringList>
#include "Usuario.h"

/**
 * @brief Classe controladora (Singleton/Manager) responsável pela lógica de negócios.
 * Expõe métodos Q_INVOKABLE para serem chamados diretamente pela interface QML (iOS/Android).
 */
class GerenciadorUsuarios : public QObject {
    Q_OBJECT

private:
    QVector<Usuario*> m_usuarios;

public:
    explicit GerenciadorUsuarios(QObject *parent = nullptr);
    ~GerenciadorUsuarios();

    /**
     * @brief Cadastra um novo cliente no sistema.
     * @return true se sucesso, false caso contrário.
     */
    Q_INVOKABLE bool cadastrarCliente(const QString& nome, const QString& email);

    /**
     * @brief Cadastra um novo fornecedor no sistema.
     * @return true se sucesso, false caso contrário.
     */
    Q_INVOKABLE bool cadastrarFornecedor(const QString& nome, const QString& email, const QString& servico);

    /**
     * @brief Busca fornecedores pelo nome ou serviço oferecido.
     * @param termo Termo de busca.
     * @return QStringList com os dados formatados dos fornecedores encontrados.
     */
    Q_INVOKABLE QStringList buscarFornecedores(const QString& termo);

    // Método auxiliar para os testes
    int getQuantidadeUsuarios() const;
};

#endif // GERENCIADORUSUARIOS_H
