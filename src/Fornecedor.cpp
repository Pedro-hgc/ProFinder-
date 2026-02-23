#include "../include/Fornecedor.h"
#include <QVariant>

Fornecedor::Fornecedor(const QString& nome, const QString& email,
                       const QString& cpf, const QString& dataNascimento, const QString& fotoPerfil,
                       const QString& certificadoAntecedentes,
                       const QStringList& fotosServico, const QString& descricaoTrabalho,
                       QVariantMap& servicosComAnos, qsizetype id )
    : Usuario(nome, email, cpf, dataNascimento, fotoPerfil, id ),
      certificadoAntecedentes(certificadoAntecedentes),
      fotosServico(fotosServico), descricaoTrabalho(descricaoTrabalho),
      servicosComAnos(servicosComAnos) {}

QString Fornecedor::getTipo() const { return "FORNECEDOR"; }

QString Fornecedor::getCertificadoAntecedentes() const { return certificadoAntecedentes; }
QStringList Fornecedor::getFotosServico() const { return fotosServico; }
QString Fornecedor::getDescricaoTrabalho() const { return descricaoTrabalho; }
QVariantMap& Fornecedor::getServicosComAnos() const { return servicosComAnos; }

void Fornecedor::setCertificadoAntecedentes(const QString& certificado) { certificadoAntecedentes = certificado; }
void Fornecedor::setFotosServico(const QStringList& fotos) { fotosServico = fotos; }
void Fornecedor::setDescricaoTrabalho(const QString& descricao) { descricaoTrabalho = descricao; }
void Fornecedor::setServicosComAnos(const QVariantMap& servicos) { servicosComAnos = servicos; }

void Fornecedor::adicionarServico(const QString& servico, int anos) {
    QVariant _variant_age(anos);
    servicosComAnos.insert(servico, _variant_age);
}

void Fornecedor::removerServico(const QString& servico) {
    servicosComAnos.remove(servico);
}

QStringList Fornecedor::getListaServicos() const {
    return servicosComAnos.keys();
}

QString Fornecedor::getServico() const {
    // Returns first service for backward compatibility
    if (servicosComAnos.isEmpty()) return "";
    return servicosComAnos.keys().first();
}
