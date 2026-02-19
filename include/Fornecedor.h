#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include "Usuario.h"

/**
 * @brief Classe que representa um Fornecedor, derivada de Usuario.
 */
class Fornecedor : public Usuario {
private:
    QString servicoOferecido;

public:
    /**
     * @brief Construtor da classe Fornecedor.
     * @param servicoOferecido O tipo de serviço que este fornecedor presta.
     */
    Fornecedor(const QString& nome, const QString& email, const QString& servicoOferecido);

    /**
     * @brief Retorna o tipo do usuário.
     * @return "Fornecedor"
     */
    QString getTipo() const override;

    /**
     * @brief Obtém o serviço oferecido pelo fornecedor.
     * @return QString contendo o serviço.
     */
    QString getServico() const;
};

#endif // FORNECEDOR_H
