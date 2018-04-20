#ifndef QTELEGRAMPLUGIN_H
#define QTELEGRAMPLUGIN_H

#include <QQmlExtensionPlugin>

class QTelegramPlugin : public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
};

#endif
