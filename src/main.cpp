#include <QGuiApplication>
#include <QMessageBox>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDir>
#include <QDebug>
#include "../include/GerenciadorUsuarios.h"
#include "../include/DatabaseManager.h"

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

    if (!DatabaseManager::instance().connect()) {
        qDebug() << "Erro de conexão: Não foi Possível se conectar com o Banco de Dados de ProFinder!";
        return -1;
    }

    qDebug() << "Conectado ao banco de dados com sucesso!" ;

    return app.exec();
}
