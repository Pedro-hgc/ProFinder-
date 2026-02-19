#include "../include/Fornecedor.h"

Fornecedor::Fornecedor(const QString& nome, const QString& email, const QString& servico)
    : Usuario(nome, email), servicoOferecido(servico) {}

QString Fornecedor::getTipo() const { return "Fornecedor"; }
QString Fornecedor::getServico() const { return servicoOferecido; }
