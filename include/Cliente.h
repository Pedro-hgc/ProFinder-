#ifndef CLIENTE_H
#define CLIENTE_H

#include "Usuario.h"

/**
 * @brief Classe que representa um Cliente, derivada de Usuario.
 */
class Cliente : public Usuario {
public:
    /**
     * @brief Construtor da classe Cliente.
     * @param nome Nome do cliente.
     * @param email Email do cliente.
     * @param cpf CPF do cliente.
     * @param dataNascimento Data de nascimento no formato YYYY-MM-DD.
     * @param fotoPerfil Caminho ou base64 da foto de perfil.
     */
    Cliente(const QString& nome, const QString& email, const QString& cpf,
            const QString& dataNascimento, const QString& fotoPerfil);

    /**
     * @brief Retorna o tipo do usuário.
     * @return "Cliente"
     */
    QString getTipo() const override;
};

#endif // CLIENTE_H
