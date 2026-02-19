#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include "../include/GerenciadorUsuarios.h"

int main(int argc, char *argv[]) {
    QGuiApplication::setApplicationName("ProFinder version 0.0.1");
    QGuiApplication::setOrganizationName("ProFinder corp.");

    QGuiApplication app(argc, argv);

    GerenciadorUsuarios gerenciador;
    gerenciador.cadastrarFornecedor("Carlos Encanador", "carlos@email.com", "Hidráulica");
    gerenciador.cadastrarFornecedor("Maria Eletricista", "maria@email.com", "Elétrica");

    QQmlApplicationEngine engine;

    // Adiciona a pasta 'ui' como caminho de importação para que o main.qml ache as outras telas
    engine.addImportPath(QDir::currentPath() + "/ui");

    // Expõe o backend
    engine.rootContext()->setContextProperty("gerenciador", &gerenciador);

    // Carrega o container principal
    engine.load(QUrl::fromLocalFile("./ui/main.qml"));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
