#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include "../include/GerenciadorUsuarios.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    // O construtor do GerenciadorUsuarios já chamará carregarDados()
    GerenciadorUsuarios gerenciador;

    QQmlApplicationEngine engine;
    engine.addImportPath(QDir::currentPath() + "/ui");
    engine.rootContext()->setContextProperty("gerenciador", &gerenciador);

    engine.load(QUrl::fromLocalFile("./ui/main.qml"));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
