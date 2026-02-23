#include "../include/GerenciadorUsuarios.h"
#include "../include/Cliente.h"
#include "../include/Fornecedor.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>


GerenciadorUsuarios::GerenciadorUsuarios(QObject *parent) : QObject(parent), m_usuarioLogado(nullptr) {
}

GerenciadorUsuarios::~GerenciadorUsuarios() {
}


bool GerenciadorUsuarios::cadastrarCliente(const QString& nome, const QString& email, const QString& cpf, const QString& dataNascimento, const QString& fotoPerfil) {
    // TODO: Implement the cadastrarCliente() Method

    return true;

}

bool GerenciadorUsuarios::cadastrarFornecedor(const QString& nome, const QString& email, const QString& cpf, const QString& dataNascimento, const QString& fotoPerfil, const QString& cpfCnpj, const QString& certificado, const QStringList& fotosServico, const QString& descricao, const QVariantMap& servicos) {
    // TODO: Implement the cadastrarFornecedor() Method

    return true;
}

/*QVariantMap GerenciadorUsuarios::fazerLogin(const QString& email, const QString& cpf) {
    // TODO: Implement the fazerLogin() Method

}*/

//QVariantMap GerenciadorUsuarios::obterDetalhesFornecedor(int index) {
    // TODO

//}

/*
QVariantMap GerenciadorUsuarios::getUsuarioLogado() {
    QVariantMap res; res["logado"] = (m_usuarioLogado != nullptr);
    if (m_usuarioLogado) { res["nome"] = m_usuarioLogado->getNome(); res["tipo"] = m_usuarioLogado->getTipo(); }
    return res;
}
*/
//void GerenciadorUsuarios::fazerLogout() { m_usuarioLogado = nullptr; }
/*
int GerenciadorUsuarios::getIndiceFornecedor(const QString& nome) {
    // TODO
    return 0;
}*/

/*
QStringList GerenciadorUsuarios::buscarFornecedores(const QString& termo) {
    QStringList nomes;
    for(Usuario* u : m_usuarios) if(u->getTipo() == "Fornecedor" && u->getNome().contains(termo, Qt::CaseInsensitive)) nomes << u->getNome();
    return nomes;
}*/
