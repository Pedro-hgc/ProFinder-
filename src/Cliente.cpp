#include "../include/Cliente.h"

Cliente::Cliente(const QString& nome, const QString& email, const QString& cpf,
                 const QString& dataNascimento, const QString& fotoPerfil)
    : Usuario(nome, email, cpf, dataNascimento, fotoPerfil) {}

QString Cliente::getTipo() const { return "Cliente"; }
