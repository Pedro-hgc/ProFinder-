##
# ProFinder
#
# @file
# @version 0.1
CXX = g++
# Adicionados Qt6Gui, Qt6Qml e Qt6Quick
QT_MODULES = Qt6Core Qt6Gui Qt6Qml Qt6Quick Qt6Test
CXXFLAGS = -fPIC -std=c++17 -I./include $(shell pkg-config --cflags $(QT_MODULES))
LDFLAGS = $(shell pkg-config --libs $(QT_MODULES))

MOC = /usr/lib/qt6/moc

SRC_DIR = src
INC_DIR = include
OBJ_DIR = objs
TEST_DIR = tests
UI_DIR = ui

# Fontes do Core
CORE_SRCS = $(SRC_DIR)/Usuario.cpp $(SRC_DIR)/Cliente.cpp $(SRC_DIR)/Fornecedor.cpp $(SRC_DIR)/GerenciadorUsuarios.cpp
CORE_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CORE_SRCS))

# Fonte da UI (main.cpp)
APP_SRC = $(SRC_DIR)/main.cpp
APP_OBJ = $(OBJ_DIR)/main.o

# Objetos MOC
MOC_SRC = $(OBJ_DIR)/moc_GerenciadorUsuarios.cpp
MOC_OBJ = $(OBJ_DIR)/moc_GerenciadorUsuarios.o
TEST_MOC = $(TEST_DIR)/test_funcionais.moc

TARGET_LIB = $(OBJ_DIR)/libcore.a
TEST_EXEC = $(OBJ_DIR)/test_runner
APP_EXEC = app_mvp

# Regra principal
all: dirs $(TARGET_LIB) $(TEST_MOC) $(TEST_EXEC) $(APP_EXEC)

dirs:
	mkdir -p $(OBJ_DIR)

# MOC rules
$(MOC_SRC): $(INC_DIR)/GerenciadorUsuarios.h
	$(MOC) $< -o $@

$(TEST_MOC): $(TEST_DIR)/test_funcionais.cpp
	$(MOC) $< -o $@

# Compilar objetos
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(MOC_OBJ): $(MOC_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Biblioteca Estática
$(TARGET_LIB): $(CORE_OBJS) $(MOC_OBJ)
	ar rcs $@ $^

# Executável de Testes
$(TEST_EXEC): $(TEST_DIR)/test_funcionais.cpp $(TEST_MOC) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $< -L$(OBJ_DIR) -lcore $(LDFLAGS) -o $@

# Executável Principal (App QML)
$(APP_EXEC): $(APP_OBJ) $(TARGET_LIB)
	$(CXX) $(CXXFLAGS) $< -L$(OBJ_DIR) -lcore $(LDFLAGS) -o $@

test: dirs $(TARGET_LIB) $(TEST_MOC) $(TEST_EXEC)
	./$(TEST_EXEC)

run: dirs $(TARGET_LIB) $(APP_EXEC)
	./$(APP_EXEC)

clean:
	rm -rf $(OBJ_DIR) $(TEST_DIR)/*.moc $(APP_EXEC)

.PHONY: all test run clean dirs
# end
