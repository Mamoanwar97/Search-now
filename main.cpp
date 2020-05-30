#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>

#include "handletextfield.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
        const QUrl url(QStringLiteral("qrc:/main.qml"));
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
        engine.load(url);




    HandleTextField handleTextField;

    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    // connect our QML signal to our C++ slot
    QObject::connect(window, SIGNAL(submitTextField(QString)),
                         &handleTextField, SLOT(handleSubmitTextField(QString)));

    QObject::connect(window, SIGNAL(searchTextField(QString)),
                         &handleTextField, SLOT(handleSearchTextField(QString)));
    QObject::connect(window, SIGNAL(openFileInQml(QString,QString)),
                         &handleTextField, SLOT(handleOpenFileInQml(QString,QString)));

    // connect our C++ signal to our QML slot
    //to pass an parameter to our QML slot, it has to be
    // a QVariant.
    QObject::connect(&handleTextField, SIGNAL(setTextField(QVariant)),
                         window, SLOT(setTextField(QVariant)));
    QObject::connect(&handleTextField, SIGNAL(listFileNames(QVariant)),
                         window, SLOT(listFileNames(QVariant)));
    QObject::connect(&handleTextField, SIGNAL(viewFileInTextArea(QVariant)),
                         window, SLOT(viewFileInTextArea(QVariant)));

    return app.exec();
}
