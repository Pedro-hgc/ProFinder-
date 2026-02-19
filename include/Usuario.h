#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

/**
 * @brief Classe base que representa um Usuário genérico no sistema.
 */
class Usuario {
protected:
    QString nome;
    QString email;

public:
    /**
     * @brief Construtor da classe Usuario.
     * @param nome Nome do usuário.
     * @param email Email do usuário.
     */
    Usuario(const QString& nome, const QString& email);

    virtual ~Usuario() = default;

    /**
     * @brief Obtém o nome do usuário.
     * @return QString contendo o nome.
     */
    QString getNome() const;

    /**
     * @brief Obtém o email do usuário.
     * @return QString contendo o email.
     */
    QString getEmail() const;

    /**
     * @brief Método virtual puro para identificar o tipo de usuário.
     * @return QString representando o tipo ("Cliente" ou "Fornecedor").
     */
    virtual QString getTipo() const = 0;
};

#endif // USUARIO_H
