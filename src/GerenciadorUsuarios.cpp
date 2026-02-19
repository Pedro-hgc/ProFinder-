#include "../include/GerenciadorUsuarios.h"
#include "../include/Cliente.h"
#include "../include/Fornecedor.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

GerenciadorUsuarios::GerenciadorUsuarios(QObject *parent) : QObject(parent), m_usuarioLogado(nullptr) {
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
        userObj["cpf"] = u->getCpf();
        userObj["dataNascimento"] = u->getDataNascimento();
        userObj["fotoPerfil"] = u->getFotoPerfil();

        if (u->getTipo() == "Fornecedor") {
            const Fornecedor* f = static_cast<const Fornecedor*>(u);
            userObj["cpfCnpj"] = f->getCpfCnpj();
            userObj["certificadoAntecedentes"] = f->getCertificadoAntecedentes();
            userObj["descricaoTrabalho"] = f->getDescricaoTrabalho();
            
            // Save photos array
            QJsonArray fotosArray;
            for (const QString& foto : f->getFotosServico()) {
                fotosArray.append(foto);
            }
            userObj["fotosServico"] = fotosArray;
            
            // Save services map
            QJsonObject servicosObj;
            QMap<QString, int> servicos = f->getServicosComAnos();
            for (auto it = servicos.begin(); it != servicos.end(); ++it) {
                servicosObj[it.key()] = it.value();
            }
            userObj["servicosComAnos"] = servicosObj;
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

        // Common fields for all users
        QString cpf = obj.contains("cpf") ? obj["cpf"].toString() : "";
        QString dataNascimento = obj.contains("dataNascimento") ? obj["dataNascimento"].toString() : "";
        QString fotoPerfil = obj.contains("fotoPerfil") ? obj["fotoPerfil"].toString() : "";
        
        if (tipo == "Cliente") {
            m_usuarios.append(new Cliente(obj["nome"].toString(), obj["email"].toString(),
                                         cpf, dataNascimento, fotoPerfil));
        } else if (tipo == "Fornecedor") {
            // Backward compatibility: check if old format exists
            if (obj.contains("servico") && !obj.contains("servicosComAnos")) {
                // Old format - convert to new format
                QString servico = obj["servico"].toString();
                QMap<QString, int> servicosComAnos;
                servicosComAnos[servico] = 0; // Default to 0 years for old data
                
                QStringList fotosServico;
                QString cpfCnpj = obj.contains("cpfCnpj") ? obj["cpfCnpj"].toString() : cpf;
                QString certificado = obj.contains("certificadoAntecedentes") ? obj["certificadoAntecedentes"].toString() : "";
                QString descricao = obj.contains("descricaoTrabalho") ? obj["descricaoTrabalho"].toString() : "";
                
                m_usuarios.append(new Fornecedor(obj["nome"].toString(),
                                                obj["email"].toString(),
                                                cpf, dataNascimento, fotoPerfil,
                                                cpfCnpj, certificado, fotosServico,
                                                descricao, servicosComAnos));
            } else {
                // New format
                QStringList fotosServico;
                QJsonArray fotosArray = obj["fotosServico"].toArray();
                for (const QJsonValue& foto : fotosArray) {
                    fotosServico.append(foto.toString());
                }
                
                QMap<QString, int> servicosComAnos;
                QJsonObject servicosObj = obj["servicosComAnos"].toObject();
                for (auto it = servicosObj.begin(); it != servicosObj.end(); ++it) {
                    servicosComAnos[it.key()] = it.value().toInt();
                }
                
                QString cpfCnpj = obj.contains("cpfCnpj") ? obj["cpfCnpj"].toString() : cpf;
                
                m_usuarios.append(new Fornecedor(obj["nome"].toString(),
                                                obj["email"].toString(),
                                                cpf, dataNascimento, fotoPerfil,
                                                cpfCnpj,
                                                obj["certificadoAntecedentes"].toString(),
                                                fotosServico,
                                                obj["descricaoTrabalho"].toString(),
                                                servicosComAnos));
            }
        }
    }
    file.close();
}

bool GerenciadorUsuarios::cadastrarCliente(const QString& nome, const QString& email,
                                           const QString& cpf, const QString& dataNascimento,
                                           const QString& fotoPerfil) {
    if (nome.isEmpty() || email.isEmpty() || cpf.isEmpty() || 
        dataNascimento.isEmpty() || fotoPerfil.isEmpty()) return false;
    Cliente* novoCliente = new Cliente(nome, email, cpf, dataNascimento, fotoPerfil);
    m_usuarios.append(novoCliente);
    m_usuarioLogado = novoCliente; // Auto-login after registration
    salvarDados();

    emit dadosAlterados();
    emit clienteAdicionado();
    return true;
}

bool GerenciadorUsuarios::cadastrarFornecedor(const QString& nome, const QString& email,
                                              const QString& cpf, const QString& dataNascimento,
                                              const QString& fotoPerfil,
                                              const QString& cpfCnpj, const QString& certificadoAntecedentes,
                                              const QStringList& fotosServico, const QString& descricaoTrabalho,
                                              const QVariantMap& servicosComAnos) {
    // Validation
    if (nome.isEmpty() || email.isEmpty() || cpf.isEmpty() || dataNascimento.isEmpty() ||
        fotoPerfil.isEmpty() || cpfCnpj.isEmpty() || certificadoAntecedentes.isEmpty()) {
        return false;
    }
    
    // Validate photos (1-5 required)
    if (fotosServico.isEmpty() || fotosServico.size() > 5) {
        return false;
    }
    
    // Validate at least one service
    if (servicosComAnos.isEmpty()) {
        return false;
    }
    
    // Convert QVariantMap to QMap<QString, int>
    QMap<QString, int> servicosMap;
    for (auto it = servicosComAnos.begin(); it != servicosComAnos.end(); ++it) {
        servicosMap[it.key()] = it.value().toInt();
    }
    
    Fornecedor* novoFornecedor = new Fornecedor(nome, email, cpf, dataNascimento, fotoPerfil,
                                                cpfCnpj, certificadoAntecedentes,
                                                fotosServico, descricaoTrabalho, servicosMap);
    m_usuarios.append(novoFornecedor);
    m_usuarioLogado = novoFornecedor; // Auto-login after registration
    salvarDados();

    emit dadosAlterados();
    emit fornecedorAdicionado();
    return true;
}

QStringList GerenciadorUsuarios::buscarFornecedores(const QString& termo) {
    QStringList resultados;
    int fornecedorIndex = 0;
    for (Usuario* u : m_usuarios) {
        if (u->getTipo() == "Fornecedor") {
            Fornecedor* f = static_cast<Fornecedor*>(u);
            QStringList servicos = f->getListaServicos();
            QString servicosStr = servicos.join(", ");
            
            // Search in name, email, services, or CPF/CNPJ
            bool matches = termo.isEmpty() || 
                          f->getNome().contains(termo, Qt::CaseInsensitive) ||
                          f->getEmail().contains(termo, Qt::CaseInsensitive) ||
                          f->getCpfCnpj().contains(termo, Qt::CaseInsensitive);
            
            // Also search in service names
            if (!matches) {
                for (const QString& servico : servicos) {
                    if (servico.contains(termo, Qt::CaseInsensitive)) {
                        matches = true;
                        break;
                    }
                }
            }
            
            if (matches) {
                // Summarized format: Name - Services (Email) - CPF/CNPJ
                resultados.append(f->getNome() + " - " + servicosStr + " (" + f->getEmail() + ") - " + f->getCpfCnpj());
            }
            fornecedorIndex++;
        }
    }
    return resultados;
}

QVariantList GerenciadorUsuarios::buscarFornecedoresComIndices(const QString& termo) {
    QVariantList resultados;
    int fornecedorIndex = 0;
    for (Usuario* u : m_usuarios) {
        if (u->getTipo() == "Fornecedor") {
            Fornecedor* f = static_cast<Fornecedor*>(u);
            QStringList servicos = f->getListaServicos();
            QString servicosStr = servicos.join(", ");
            
            // Search in name, email, services, or CPF/CNPJ
            bool matches = termo.isEmpty() || 
                          f->getNome().contains(termo, Qt::CaseInsensitive) ||
                          f->getEmail().contains(termo, Qt::CaseInsensitive) ||
                          f->getCpfCnpj().contains(termo, Qt::CaseInsensitive);
            
            // Also search in service names
            if (!matches) {
                for (const QString& servico : servicos) {
                    if (servico.contains(termo, Qt::CaseInsensitive)) {
                        matches = true;
                        break;
                    }
                }
            }
            
            if (matches) {
                QVariantMap item;
                item["display"] = f->getNome() + " - " + servicosStr + " (" + f->getEmail() + ") - " + f->getCpfCnpj();
                item["index"] = fornecedorIndex;
                item["nome"] = f->getNome();
                resultados.append(item);
            }
            fornecedorIndex++;
        }
    }
    return resultados;
}

QVariantMap GerenciadorUsuarios::obterDetalhesFornecedor(int index) {
    QVariantMap detalhes;
    int fornecedorIndex = 0;
    
    for (Usuario* u : m_usuarios) {
        if (u->getTipo() == "Fornecedor") {
            if (fornecedorIndex == index) {
                Fornecedor* f = static_cast<Fornecedor*>(u);
                detalhes["nome"] = f->getNome();
                detalhes["email"] = f->getEmail();
                detalhes["cpfCnpj"] = f->getCpfCnpj();
                detalhes["certificadoAntecedentes"] = f->getCertificadoAntecedentes();
                detalhes["fotoPerfil"] = f->getFotoPerfil();
                detalhes["descricaoTrabalho"] = f->getDescricaoTrabalho();
                detalhes["fotosServico"] = f->getFotosServico();
                
                // Convert QMap to QVariantMap for QML
                QVariantMap servicosMap;
                QMap<QString, int> servicos = f->getServicosComAnos();
                for (auto it = servicos.begin(); it != servicos.end(); ++it) {
                    servicosMap[it.key()] = it.value();
                }
                detalhes["servicosComAnos"] = servicosMap;
                break;
            }
            fornecedorIndex++;
        }
    }
    
    return detalhes;
}

int GerenciadorUsuarios::getIndiceFornecedor(const QString& nome) {
    int fornecedorIndex = 0;
    for (Usuario* u : m_usuarios) {
        if (u->getTipo() == "Fornecedor") {
            if (u->getNome() == nome) {
                return fornecedorIndex;
            }
            fornecedorIndex++;
        }
    }
    return -1;
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

QVariantMap GerenciadorUsuarios::fazerLogin(const QString& email, const QString& cpf) {
    QVariantMap resultado;
    resultado["sucesso"] = false;
    
    for (Usuario* u : m_usuarios) {
        if (u->getEmail() == email && u->getCpf() == cpf) {
            m_usuarioLogado = u;
            resultado["sucesso"] = true;
            resultado["tipo"] = u->getTipo();
            resultado["nome"] = u->getNome();
            resultado["email"] = u->getEmail();
            resultado["cpf"] = u->getCpf();
            resultado["fotoPerfil"] = u->getFotoPerfil();
            return resultado;
        }
    }
    
    return resultado;
}

QVariantMap GerenciadorUsuarios::getUsuarioLogado() {
    QVariantMap resultado;
    
    if (m_usuarioLogado) {
        resultado["tipo"] = m_usuarioLogado->getTipo();
        resultado["nome"] = m_usuarioLogado->getNome();
        resultado["email"] = m_usuarioLogado->getEmail();
        resultado["cpf"] = m_usuarioLogado->getCpf();
        resultado["fotoPerfil"] = m_usuarioLogado->getFotoPerfil();
        resultado["logado"] = true;
    } else {
        resultado["logado"] = false;
    }
    
    return resultado;
}

void GerenciadorUsuarios::fazerLogout() {
    m_usuarioLogado = nullptr;
}
