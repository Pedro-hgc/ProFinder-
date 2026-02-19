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
     */
    Cliente(const QString& nome, const QString& email);

    /**
     * @brief Retorna o tipo do usuário.
     * @return "Cliente"
     */
    QString getTipo() const override;
};

#endif // CLIENTE_H
