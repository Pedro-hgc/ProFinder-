##
# ProFinder
#
# @file
# @version 0.1
CXX = g++
CXXFLAGS = -fPIC -std=c++17 -I./include $(shell pkg-config --cflags Qt6Core Qt6Test)
LDFLAGS = $(shell pkg-config --libs Qt6Core Qt6Test)

# Caminho exato que você indicou
MOC = /usr/lib/qt6/moc

SRC_DIR = src
INC_DIR = include
OBJ_DIR = objs
TEST_DIR = tests

# Fontes do Core
CORE_SRCS = $(SRC_DIR)/Usuario.cpp $(SRC_DIR)/Cliente.cpp $(SRC_DIR)/Fornecedor.cpp $(SRC_DIR)/GerenciadorUsuarios.cpp
CORE_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CORE_SRCS))

# Objetos MOC
MOC_SRC = $(OBJ_DIR)/moc_GerenciadorUsuarios.cpp
MOC_OBJ = $(OBJ_DIR)/moc_GerenciadorUsuarios.o
TEST_MOC = $(TEST_DIR)/test_funcionais.moc

TARGET_LIB = $(OBJ_DIR)/libcore.a
TEST_EXEC = $(OBJ_DIR)/test_runner

# Regra principal
all: dirs $(TARGET_LIB) $(TEST_MOC) $(TEST_EXEC)

# Garante que a pasta de objetos exista
dirs:
	mkdir -p $(OBJ_DIR)

# 1. Gerar arquivo moc para o GerenciadorUsuarios
$(MOC_SRC): $(INC_DIR)/GerenciadorUsuarios.h
	$(MOC) $< -o $@

# 2. Gerar o .moc do arquivo de testes
$(TEST_MOC): $(TEST_DIR)/test_funcionais.cpp
	$(MOC) $< -o $@

# 3. Compilar objetos padrão
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 4. Compilar o arquivo moc gerado
$(MOC_OBJ): $(MOC_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 5. Criar biblioteca estática
$(TARGET_LIB): $(CORE_OBJS) $(MOC_OBJ)
	ar rcs $@ $^

# 6. Compilar e linkar executável de testes
$(TEST_EXEC): $(TEST_DIR)/test_funcionais.cpp $(TEST_MOC) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $< -L$(OBJ_DIR) -lcore $(LDFLAGS) -o $@

test: all
	./$(TEST_EXEC)

clean:
	rm -rf $(OBJ_DIR) $(TEST_DIR)/*.moc

.PHONY: all test clean dirs
# end
