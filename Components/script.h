#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include <QJSEngine>
#include <QString>
struct Script
{
    Script(QString fileName) : file_(fileName)
    {
        engine_ = new QJSEngine();
        engine_->installExtensions(QJSEngine::ConsoleExtension);
    }
    Script() = default;
    ~Script()
    {
    }
    QString file_ = "";
    QJSEngine* engine_;
};

#endif // SCRIPTCOMPONENT_H
