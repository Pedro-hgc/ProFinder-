#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include "Usuario.h"
#include <QMap>
#include <QStringList>

/**
 * @brief Classe que representa um Fornecedor, derivada de Usuario.
 */
class Fornecedor : public Usuario {
private:
    QString cpfCnpj; // CPF or CNPJ (can be different from base CPF for companies)
    QString certificadoAntecedentes; // Path or base64 encoded certificate
    QStringList fotosServico; // List of paths or base64 encoded images (1-5 photos)
    QString descricaoTrabalho; // Optional description
    QMap<QString, int> servicosComAnos; // Map of service name -> years of experience

public:
    /**
     * @brief Construtor da classe Fornecedor.
     * @param nome Nome do fornecedor.
     * @param email Email do fornecedor.
     * @param cpf CPF do fornecedor (para base Usuario).
     * @param dataNascimento Data de nascimento no formato YYYY-MM-DD.
     * @param fotoPerfil Foto de perfil do fornecedor (para base Usuario).
     * @param cpfCnpj CPF ou CNPJ do fornecedor (pode ser CNPJ para empresas).
     * @param certificadoAntecedentes Certificado de antecedentes criminais.
     * @param fotosServico Lista de fotos do serviço (1-5 fotos).
     * @param descricaoTrabalho Descrição opcional de como trabalha.
     * @param servicosComAnos Mapa de serviços oferecidos com anos de experiência.
     */
    Fornecedor(const QString& nome, const QString& email, 
               const QString& cpf, const QString& dataNascimento, const QString& fotoPerfil,
               const QString& cpfCnpj, const QString& certificadoAntecedentes,
               const QStringList& fotosServico, const QString& descricaoTrabalho,
               const QMap<QString, int>& servicosComAnos);

    /**
     * @brief Retorna o tipo do usuário.
     * @return "Fornecedor"
     */
    QString getTipo() const override;

    // Getters
    QString getCpfCnpj() const;
    QString getCertificadoAntecedentes() const;
    QStringList getFotosServico() const;
    QString getDescricaoTrabalho() const;
    QMap<QString, int> getServicosComAnos() const;
    
    // Setters
    void setCpfCnpj(const QString& cpfCnpj);
    void setCertificadoAntecedentes(const QString& certificado);
    void setFotosServico(const QStringList& fotos);
    void setDescricaoTrabalho(const QString& descricao);
    void setServicosComAnos(const QMap<QString, int>& servicos);
    
    // Helper methods
    void adicionarServico(const QString& servico, int anos);
    void removerServico(const QString& servico);
    QStringList getListaServicos() const; // Returns list of service names
    QString getServico() const; // Returns first service for backward compatibility
};

#endif // FORNECEDOR_H
