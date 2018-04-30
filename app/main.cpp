#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QJsonObject>
#include <QDebug>
#include <QuickFlux>
#include <qtdlib/quick/plugin.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QCoreApplication::setApplicationName(QStringLiteral("telegram-plus"));
    QCoreApplication::setApplicationVersion(QStringLiteral("0.0.1"));

    registerQuickFluxQmlTypes();
    QTdLib::registerQmlTypes();

    QQmlApplicationEngine engine;
    engine.addImportPath(QStringLiteral("qrc:/imports"));
    engine.load("qrc:/Main.qml");

    return app.exec();
}
