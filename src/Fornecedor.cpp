#include "../include/Fornecedor.h"

Fornecedor::Fornecedor(const QString& nome, const QString& email,
                       const QString& cpf, const QString& dataNascimento, const QString& fotoPerfil,
                       const QString& cpfCnpj, const QString& certificadoAntecedentes,
                       const QStringList& fotosServico, const QString& descricaoTrabalho,
                       const QMap<QString, int>& servicosComAnos)
    : Usuario(nome, email, cpf, dataNascimento, fotoPerfil), 
      cpfCnpj(cpfCnpj), certificadoAntecedentes(certificadoAntecedentes),
      fotosServico(fotosServico), descricaoTrabalho(descricaoTrabalho),
      servicosComAnos(servicosComAnos) {}

QString Fornecedor::getTipo() const { return "Fornecedor"; }

QString Fornecedor::getCpfCnpj() const { return cpfCnpj; }
QString Fornecedor::getCertificadoAntecedentes() const { return certificadoAntecedentes; }
QStringList Fornecedor::getFotosServico() const { return fotosServico; }
QString Fornecedor::getDescricaoTrabalho() const { return descricaoTrabalho; }
QMap<QString, int> Fornecedor::getServicosComAnos() const { return servicosComAnos; }

void Fornecedor::setCpfCnpj(const QString& cpfCnpj) { this->cpfCnpj = cpfCnpj; }
void Fornecedor::setCertificadoAntecedentes(const QString& certificado) { certificadoAntecedentes = certificado; }
void Fornecedor::setFotosServico(const QStringList& fotos) { fotosServico = fotos; }
void Fornecedor::setDescricaoTrabalho(const QString& descricao) { descricaoTrabalho = descricao; }
void Fornecedor::setServicosComAnos(const QMap<QString, int>& servicos) { servicosComAnos = servicos; }

void Fornecedor::adicionarServico(const QString& servico, int anos) {
    servicosComAnos[servico] = anos;
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
