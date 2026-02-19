#include "../include/Cliente.h"

Cliente::Cliente(const QString& nome, const QString& email)
    : Usuario(nome, email) {}

QString Cliente::getTipo() const { return "Cliente"; }
