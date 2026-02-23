CREATE TYPE tipo_usuario_enum AS ENUM ('CLIENTE', 'FORNECEDOR');

-- ==========================================
-- 1. BASE TABLE: Usuarios
-- ==========================================
CREATE TABLE usuarios (
    id SERIAL PRIMARY KEY,
    tipo_usuario tipo_usuario_enum NOT NULL,
    nome VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    cpf VARCHAR(14) UNIQUE NOT NULL,
    data_nascimento DATE NOT NULL,
    foto_perfil TEXT,
    criado_em TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- ==========================================
-- 2. DERIVED TABLE: Fornecedores
-- ==========================================
CREATE TABLE fornecedores (
    usuario_id INT PRIMARY KEY,
    cpf_cnpj VARCHAR(18) NOT NULL,
    certificado_antecedentes TEXT,
    descricao_trabalho TEXT,
    FOREIGN KEY (usuario_id) REFERENCES usuarios(id) ON DELETE CASCADE
);

-- ==========================================
-- 3. ONE-TO-MANY: Fotos do Serviço
-- ==========================================
CREATE TABLE fornecedor_fotos (
    id SERIAL PRIMARY KEY,
    fornecedor_id INT NOT NULL,
    foto TEXT NOT NULL,
    FOREIGN KEY (fornecedor_id) REFERENCES fornecedores(usuario_id) ON DELETE CASCADE
);

-- ==========================================
-- 4. ONE-TO-MANY: Serviços e Experiência
-- ==========================================
CREATE TABLE fornecedor_servicos (
    id SERIAL PRIMARY KEY,
    fornecedor_id INT NOT NULL,
    nome_servico VARCHAR(100) NOT NULL,
    anos_experiencia INT NOT NULL DEFAULT 0,
    FOREIGN KEY (fornecedor_id) REFERENCES fornecedores(usuario_id) ON DELETE CASCADE
);

-- ==========================================
-- VIEWS
-- ==========================================

-- VIEW: List all users together
CREATE VIEW vw_todos_usuarios AS
SELECT id, tipo_usuario, nome, email, cpf, data_nascimento
FROM usuarios;

-- VIEW: List ONLY Clients
CREATE VIEW vw_clientes AS
SELECT id, nome, email, cpf, data_nascimento, foto_perfil
FROM usuarios
WHERE tipo_usuario = 'CLIENTE';

-- VIEW: List ONLY Providers (Joined with their specific info)
CREATE VIEW vw_fornecedores_detalhes AS
SELECT
    u.id, u.nome, u.email, u.cpf, u.data_nascimento, u.foto_perfil,
    f.cpf_cnpj, f.descricao_trabalho
FROM usuarios u
JOIN fornecedores f ON u.id = f.usuario_id
WHERE u.tipo_usuario = 'FORNECEDOR';
