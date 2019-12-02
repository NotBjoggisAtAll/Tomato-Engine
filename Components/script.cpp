#include "script.h"

Script::Script(QString fileName) : file_(fileName)
{
    engine_ = new QJSEngine();
    engine_->installExtensions(QJSEngine::ConsoleExtension);
}

Script::Script(QJsonObject Json)
{
    fromJson(Json);
}

void Script::fromJson(QJsonObject Json)
{
    if(!Json.contains("file")) return;

    if(engine_)
        delete engine_;
    engine_ = new QJSEngine();
    engine_->installExtensions(QJSEngine::ConsoleExtension);

    file_ = Json.take("file").toString();
}

QJsonObject Script::toJson()
{
    QJsonObject object;
    object.insert("file", file_);
    return object;
}
