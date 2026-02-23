#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

/**
 * @brief Classe base que representa um Usuário genérico no sistema.
 */
class Usuario {
protected:
    QString nome;
    QString email;
    QString cpf;
    QString dataNascimento; // Format: YYYY-MM-DD
    QString fotoPerfil; // Path or base64 encoded image
    qsizetype id;

public:
    /**
     * @brief Construtor da classe Usuario.
     * @param nome Nome do usuário.
     * @param email Email do usuário.
     * @param cpf CPF do usuário.
     * @param dataNascimento Data de nascimento no formato YYYY-MM-DD.
     * @param fotoPerfil Caminho ou base64 da foto de perfil.
     */
    Usuario(const QString& nome, const QString& email, const QString& cpf, 
            const QString& dataNascimento, const QString& fotoPerfil, const qsizetype id);

    virtual ~Usuario() = default;

    /**
     * @brief Obtém o nome do usuário.
     * @return QString contendo o nome.
     */
    QString getNome() const;

    /**
     * @brief Obtém o email do usuário.
     * @return QString contendo o email.
     */
    QString getEmail() const;

    /**
     * @brief Obtém o CPF do usuário.
     * @return QString contendo o CPF.
     */
    QString getCpf() const;

    /**
     * @brief Obtém a data de nascimento do usuário.
     * @return QString contendo a data no formato YYYY-MM-DD.
     */
    QString getDataNascimento() const;

    /**
     * @brief Obtém a foto de perfil do usuário.
     * @return QString contendo o caminho ou base64 da foto.
     */
    QString getFotoPerfil() const;


    /**
     * @brief Obtém o ID do usuário
     * @return size_t contendo o ID do usuário
     */
    size_t getId() const ;

    /**
     * @brief Define o nome do usuário.
     * @param nome Novo nome do usuário.
     */
    void setNome(const QString& nome);

    /**
     * @brief Define o email do usuário.
     * @param email Novo email do usuário.
     */
    void setEmail(const QString& email);

    /**
     * @brief Define o CPF do usuário.
     * @param cpf Novo CPF do usuário.
     */
    void setCpf(const QString& cpf);

    /**
     * @brief Define a data de nascimento do usuário.
     * @param dataNascimento Nova data no formato YYYY-MM-DD.
     */
    void setDataNascimento(const QString& dataNascimento);

    /**
     * @brief Define a foto de perfil do usuário.
     * @param fotoPerfil Novo caminho ou base64 da foto.
     */
    void setFotoPerfil(const QString& fotoPerfil);

    /**
     * @brief Define o ID do usuário.
     * @param id que será definido.
     */
    void setId(const qsizetype _id);
    /**
     * @brief Método virtual puro para identificar o tipo de usuário.
     * @return QString representando o tipo ("Cliente" ou "Fornecedor").
     */
    virtual QString getTipo() const = 0;
};

#endif // USUARIO_H
