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
    QString cpfCnpj;
    QString certificadoAntecedentes; // Path or base64 encoded certificate
    QStringList fotosServico; // List of paths or base64 encoded images (1-5 photos)
    QString descricaoTrabalho; // Optional description
    QString fotoPerfil; // Path or base64 encoded profile picture
    QMap<QString, int> servicosComAnos; // Map of service name -> years of experience

public:
    /**
     * @brief Construtor da classe Fornecedor.
     * @param nome Nome do fornecedor.
     * @param email Email do fornecedor.
     * @param cpfCnpj CPF ou CNPJ do fornecedor.
     * @param certificadoAntecedentes Certificado de antecedentes criminais.
     * @param fotosServico Lista de fotos do serviço (1-5 fotos).
     * @param descricaoTrabalho Descrição opcional de como trabalha.
     * @param fotoPerfil Foto de perfil do fornecedor.
     * @param servicosComAnos Mapa de serviços oferecidos com anos de experiência.
     */
    Fornecedor(const QString& nome, const QString& email, 
               const QString& cpfCnpj, const QString& certificadoAntecedentes,
               const QStringList& fotosServico, const QString& descricaoTrabalho,
               const QString& fotoPerfil, const QMap<QString, int>& servicosComAnos);

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
    QString getFotoPerfil() const;
    QMap<QString, int> getServicosComAnos() const;
    
    // Setters
    void setCpfCnpj(const QString& cpfCnpj);
    void setCertificadoAntecedentes(const QString& certificado);
    void setFotosServico(const QStringList& fotos);
    void setDescricaoTrabalho(const QString& descricao);
    void setFotoPerfil(const QString& foto);
    void setServicosComAnos(const QMap<QString, int>& servicos);
    
    // Helper methods
    void adicionarServico(const QString& servico, int anos);
    void removerServico(const QString& servico);
    QStringList getListaServicos() const; // Returns list of service names
    QString getServico() const; // Returns first service for backward compatibility
};

#endif // FORNECEDOR_H
