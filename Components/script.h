#ifndef SCRIPTCOMPONENT_H
#define SCRIPTCOMPONENT_H

#include <QJSEngine>
#include <QString>
#include <QJsonObject>
struct Script
{
    Script(QString fileName) : file_(fileName)
    {
        engine_ = new QJSEngine();
        engine_->installExtensions(QJSEngine::ConsoleExtension);
    }
    Script() = default;

    Script(QJsonObject Json)
    {
        fromJson(Json);
    }
    ~Script()
    {
    }
    QString file_ = "";
    QJSEngine* engine_ = nullptr;

    void fromJson(QJsonObject Json)
    {
        if(engine_)
            delete engine_;
        engine_ = new QJSEngine();
        engine_->installExtensions(QJSEngine::ConsoleExtension);

        file_ = Json.take("file").toString();
    }

    QJsonObject toJson()
    {
        QJsonObject object;
        object.insert("file", file_);
        return object;
    }
};

#endif // SCRIPTCOMPONENT_H
