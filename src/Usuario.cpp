#include "../include/Usuario.h"

Usuario::Usuario(const QString& nome, const QString& email, const QString& cpf,
                 const QString& dataNascimento, const QString& fotoPerfil, qsizetype id)
    : nome(nome), email(email), cpf(cpf), dataNascimento(dataNascimento), fotoPerfil(fotoPerfil), id(id) {}

QString Usuario::getNome() const { return nome; }
QString Usuario::getEmail() const { return email; }
QString Usuario::getCpf() const { return cpf; }
QString Usuario::getDataNascimento() const { return dataNascimento; }
QString Usuario::getFotoPerfil() const { return fotoPerfil; }
size_t Usuario::getId() const { return id; }

void Usuario::setNome(const QString& nome) { this->nome = nome; }
void Usuario::setEmail(const QString& email) { this->email = email; }
void Usuario::setCpf(const QString& cpf) { this->cpf = cpf; }
void Usuario::setDataNascimento(const QString& dataNascimento) { this->dataNascimento = dataNascimento; }
void Usuario::setFotoPerfil(const QString& fotoPerfil) { this->fotoPerfil = fotoPerfil; }
void Usuario::setId(const qsizetype _id) { this->id = _id; }
