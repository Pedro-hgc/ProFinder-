#include "../include/GerenciadorUsuarios.h"
#include "../include/Cliente.h"
#include "../include/Fornecedor.h"

GerenciadorUsuarios::GerenciadorUsuarios(QObject *parent) : QObject(parent) {}

GerenciadorUsuarios::~GerenciadorUsuarios() {
    qDeleteAll(m_usuarios);
    m_usuarios.clear();
}

bool GerenciadorUsuarios::cadastrarCliente(const QString& nome, const QString& email) {
    if (nome.isEmpty() || email.isEmpty()) return false;
    m_usuarios.append(new Cliente(nome, email));
    return true;
}

bool GerenciadorUsuarios::cadastrarFornecedor(const QString& nome, const QString& email, const QString& servico) {
    if (nome.isEmpty() || email.isEmpty() || servico.isEmpty()) return false;
    m_usuarios.append(new Fornecedor(nome, email, servico));
    return true;
}

QStringList GerenciadorUsuarios::buscarFornecedores(const QString& termo) {
    QStringList resultados;
    for (Usuario* u : m_usuarios) {
        if (u->getTipo() == "Fornecedor") {
            Fornecedor* f = static_cast<Fornecedor*>(u);
            // Busca simples (case insensitive) no nome ou serviço
            if (f->getNome().contains(termo, Qt::CaseInsensitive) ||
                f->getServico().contains(termo, Qt::CaseInsensitive)) {
                resultados.append(f->getNome() + " - " + f->getServico() + " (" + f->getEmail() + ")");
            }
        }
    }
    return resultados;
}

int GerenciadorUsuarios::getQuantidadeUsuarios() const {
    return m_usuarios.size();
}
