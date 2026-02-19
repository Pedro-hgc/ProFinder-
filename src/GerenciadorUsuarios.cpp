#include "../include/GerenciadorUsuarios.h"
#include "../include/Cliente.h"
#include "../include/Fornecedor.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>

GerenciadorUsuarios::GerenciadorUsuarios(QObject *parent) : QObject(parent) {
    carregarDados(); // Carrega o JSON assim que o objeto é criado
}

GerenciadorUsuarios::~GerenciadorUsuarios() {
    qDeleteAll(m_usuarios);
}

void GerenciadorUsuarios::salvarDados() {
    QJsonArray rootArray;

    for (const auto* u : m_usuarios) {
        QJsonObject userObj;
        userObj["tipo"] = u->getTipo();
        userObj["nome"] = u->getNome();
        userObj["email"] = u->getEmail();

        if (u->getTipo() == "Fornecedor") {
            const Fornecedor* f = static_cast<const Fornecedor*>(u);
            userObj["servico"] = f->getServico();
        }
        rootArray.append(userObj);
    }

    QJsonDocument doc(rootArray);
    QFile file(m_dbPath);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    }
}

void GerenciadorUsuarios::carregarDados() {
    QFile file(m_dbPath);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray rootArray = doc.array();

    for (int i = 0; i < rootArray.size(); ++i) {
        QJsonObject obj = rootArray[i].toObject();
        QString tipo = obj["tipo"].toString();

        if (tipo == "Cliente") {
            m_usuarios.append(new Cliente(obj["nome"].toString(), obj["email"].toString()));
        } else if (tipo == "Fornecedor") {
            m_usuarios.append(new Fornecedor(obj["nome"].toString(),
                                             obj["email"].toString(),
                                             obj["servico"].toString()));
        }
    }
    file.close();
}

bool GerenciadorUsuarios::cadastrarCliente(const QString& nome, const QString& email) {
    if (nome.isEmpty() || email.isEmpty()) return false;
    m_usuarios.append(new Cliente(nome, email));
    salvarDados();

    emit dadosAlterados(); // <--- AVISO PARA A INTERFACE
    emit clienteAdicionado();
    return true;
}

bool GerenciadorUsuarios::cadastrarFornecedor(const QString& nome, const QString& email, const QString& servico) {
    if (nome.isEmpty() || email.isEmpty() || servico.isEmpty()) return false;
    m_usuarios.append(new Fornecedor(nome, email, servico));
    salvarDados();

    emit dadosAlterados(); // <--- AVISO PARA A INTERFACE
    emit fornecedorAdicionado();
    return true;
}

QStringList GerenciadorUsuarios::buscarFornecedores(const QString& termo) {
    QStringList resultados;
    for (Usuario* u : m_usuarios) {
        if (u->getTipo() == "Fornecedor") {
            Fornecedor* f = static_cast<Fornecedor*>(u);
            // Se o termo for vazio, retorna todos os fornecedores (conforme solicitado)
            if (termo.isEmpty() || f->getNome().contains(termo, Qt::CaseInsensitive) ||
                f->getServico().contains(termo, Qt::CaseInsensitive)) {
                resultados.append(f->getNome() + " - " + f->getServico() + " (" + f->getEmail() + ")");
            }
        }
    }
    return resultados;
}

int GerenciadorUsuarios::getQuantidadeUsuarios() const { return m_usuarios.size(); }
int GerenciadorUsuarios::getQuantidadeFornecedores() const {
    int counting = 0;

    for (Usuario* u : m_usuarios) {
        if (u->getTipo() == "Fornecedor" )
            counting++;
}

    return counting;
}
