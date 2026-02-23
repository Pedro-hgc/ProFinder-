#include "../include/Cliente.h"

Cliente::Cliente(const QString& nome, const QString& email, const QString& cpf,
                 const QString& dataNascimento, const QString& fotoPerfil, qsizetype id)
    : Usuario(nome, email, cpf, dataNascimento, fotoPerfil, id) {}

QString Cliente::getTipo() const { return "CLIENTE"; }
