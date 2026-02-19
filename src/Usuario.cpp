#include "../include/Usuario.h"

Usuario::Usuario(const QString& nome, const QString& email)
    : nome(nome), email(email) {}

QString Usuario::getNome() const { return nome; }
QString Usuario::getEmail() const { return email; }
