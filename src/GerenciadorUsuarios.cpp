#include "../include/database/UserRepository.h"
#include "../include/GerenciadorUsuarios.h"
#include "../include/Cliente.h"
#include "../include/Fornecedor.h"


GerenciadorUsuarios::GerenciadorUsuarios(QObject *parent) : QObject(parent), m_usuarioLogado(nullptr) {
}

GerenciadorUsuarios::~GerenciadorUsuarios() {
}


QString GerenciadorUsuarios::cadastrarCliente(const QString& nome, const QString& email, const QString& cpf, const QString& dataNascimento, const QString& fotoPerfil) {
    if (nome == "") return "Erro: Preencha o campo Nome!";


    if (!email.contains('@') ) return "Erro: Insira um Email Válido!";

    if (cpf == "") return "Erro: Preencha o campo CPF!";

    if (dataNascimento == "") return "Erro: Preencha o campo Data de Nascimento!";

    if (fotoPerfil == "") return "Erro: Selecione uma foto de perfil!";


    Cliente _user(nome, email, cpf, dataNascimento, fotoPerfil);
    if (!UserRepository::insertClient(_user)) {
        return "Erro: Cliente não foi cadastrado no Banco de Dados!";
    };

    if (m_usuarioLogado) delete m_usuarioLogado;
    m_usuarioLogado = new Cliente(_user);

    return "Cliente Cadastrado com sucesso!";
}

QString GerenciadorUsuarios::cadastrarFornecedor(const QString& nome, const QString& email, const QString& cpf, const QString& dataNascimento, const QString& fotoPerfil, const QString& certificado, const QStringList& fotosServico, const QString& descricao, QVariantMap& servicos) {
    // TODO: Implement the cadastrarFornecedor() Method
    if (nome == "") return "Erro: Preencha o campo Nome!";


    if (email.contains("@")) return "Erro: Insira um Email Válido!";

    if (cpf == "") return "Erro: Preencha o campo CPF!";

    if (dataNascimento == "") return "Erro: Preencha o campo Data de Nascimento!";

    if (fotoPerfil == "") return "Erro: Selecione uma foto de perfil!";

    if (certificado == "") return "Erro: Insira um certificado de Antecedentes Criminais!";

    if (fotosServico.isEmpty() ) return "Erro: Você precisa adicionar pelo menos uma foto do seu serviço!";

    if(servicos.isEmpty()) return "Erro: Você precisa adicionar pelo menos um serviço!";

    Fornecedor _user(nome, email, cpf, dataNascimento, fotoPerfil, certificado, fotosServico, descricao, servicos);
    if (!UserRepository::insertSupplier(_user)) {
        return "Erro: Fornecedor não foi cadastrado no Banco de Dados!";
    };

    if(m_usuarioLogado) delete m_usuarioLogado;

    m_usuarioLogado = new Fornecedor(_user);
    return "Fornecedor Cadastrado com sucesso!";
}

/*QVariantMap GerenciadorUsuarios::fazerLogin(const QString& email, const QString& cpf) {
    // TODO: Implement the fazerLogin() Method

}*/

//QVariantMap GerenciadorUsuarios::obterDetalhesFornecedor(int index) {
    // TODO

//}


QVariantMap GerenciadorUsuarios::getUsuarioLogado() {
    QVariantMap res; res["logado"] = (m_usuarioLogado != nullptr);
    if (m_usuarioLogado) { res["nome"] = m_usuarioLogado->getNome(); res["tipo"] = m_usuarioLogado->getTipo(); }
    return res;
}

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
