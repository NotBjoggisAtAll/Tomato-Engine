#include "mesh.h"
#include <QJsonObject>
#include "Factories/resourcefactory.h"

Mesh::Mesh(QJsonObject Json)
{
    fromJson(Json);
}

QJsonObject Mesh::toJson()
{
    QJsonObject object;
    object.insert("visible", isVisible_);
    object.insert("filepath", QString::fromStdString(filepath_));
    object.insert("affectedByFrustum", isAffectedByFrustum_);

    return object;
}


void Mesh::fromJson(QJsonObject Json)
{
    if(!Json.contains("filepath")) return;

    Mesh m = ResourceFactory::get()->loadMesh(Json.take("filepath").toString().toStdString());
    VAO_ = m.VAO_;
    verticeCount_ = m.verticeCount_;
    indiceCount_ = m.indiceCount_;
    drawType_ = m.drawType_;
    filepath_ = m.filepath_;

    isVisible_ = Json.take("visible").toBool();
    isAffectedByFrustum_ = Json.take("affectedByFrustum").toBool();
}
