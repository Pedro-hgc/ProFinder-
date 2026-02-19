##
# ProFinder
#
# @file
# @version 0.1

CXX = g++
CXXFLAGS = -fPIC -std=c++17 -I./include $(shell pkg-config --cflags Qt6Core Qt6Test)
LDFLAGS = $(shell pkg-config --libs Qt6Core Qt6Test)
MOC = moc

SRC_DIR = src
INC_DIR = include
OBJ_DIR = objs
TEST_DIR = tests

# Fontes do Core (sem a main.cpp gráfica para a biblioteca estática)
CORE_SRCS = $(SRC_DIR)/Usuario.cpp $(SRC_DIR)/Cliente.cpp $(SRC_DIR)/Fornecedor.cpp $(SRC_DIR)/GerenciadorUsuarios.cpp
CORE_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CORE_SRCS))

# Objeto MOC
MOC_SRC = $(OBJ_DIR)/moc_GerenciadorUsuarios.cpp
MOC_OBJ = $(OBJ_DIR)/moc_GerenciadorUsuarios.o

TARGET_LIB = $(OBJ_DIR)/libcore.a
TEST_EXEC = $(OBJ_DIR)/test_runner

all: $(TARGET_LIB) $(TEST_EXEC)

# Gerar arquivo moc para o GerenciadorUsuarios (requerido pelo Q_OBJECT)
$(MOC_SRC): $(INC_DIR)/GerenciadorUsuarios.h
	@mkdir -p $(OBJ_DIR)
	$(MOC) $< -o $@

$(MOC_OBJ): $(MOC_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilar objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Criar biblioteca estática
$(TARGET_LIB): $(CORE_OBJS) $(MOC_OBJ)
	ar rcs $@ $^

# Compilar e linkar testes
$(TEST_EXEC): $(TEST_DIR)/test_funcionais.cpp $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $< -L$(OBJ_DIR) -lcore $(LDFLAGS) -o $@

test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -rf $(OBJ_DIR)/*

.PHONY: all test clean

# end
