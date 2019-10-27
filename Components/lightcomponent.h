#ifndef LIGHT_H
#define LIGHT_H

#include "gltypes.h"
#include "GSL/vector3d.h"
#include <QJsonObject>
#include <QJsonArray>

struct Light{

    Light() = default;

    GLfloat mAmbientStrenght{0.3f};
    gsl::Vector3D mAmbientColor{0.3f, 0.3f, 0.3f};

    GLfloat mLightStrenght{0.7f};
    gsl::Vector3D mLightColor{0.3f, 0.3f, 0.3f};

    GLfloat mSpecularStrenght{0.3f};
    GLint mSpecularExponent{4};

    Light(QJsonObject JSON)
    {
        QJsonObject ambientObject = JSON.take("ambient").toObject();

        mAmbientStrenght = static_cast<float>(ambientObject.take("strength").toDouble());
        QJsonArray ambientColor = ambientObject.take("color").toArray();
        mAmbientColor.x = static_cast<float>(ambientColor.at(0).toDouble());
        mAmbientColor.y = static_cast<float>(ambientColor.at(1).toDouble());
        mAmbientColor.z = static_cast<float>(ambientColor.at(2).toDouble());

        QJsonObject lightObject = JSON.take("light").toObject();

        mLightStrenght = static_cast<float>(lightObject.take("strength").toDouble());
        QJsonArray lightColor = lightObject.take("color").toArray();
        mLightColor.x = static_cast<float>(lightColor.at(0).toDouble());
        mLightColor.y = static_cast<float>(lightColor.at(1).toDouble());
        mLightColor.z = static_cast<float>(lightColor.at(2).toDouble());

        QJsonObject specularObject = JSON.take("specular").toObject();

        mSpecularStrenght = static_cast<float>(specularObject.take("strength").toDouble());
        mSpecularExponent = specularObject.take("exponent").toInt();
    }

    QJsonObject toJSON()
    {
        QJsonObject object;

        QJsonObject ambientObject;
        QJsonArray ambientColor;
        ambientColor.insert(0, QJsonValue(static_cast<double>(mAmbientColor.x)));
        ambientColor.insert(1, QJsonValue(static_cast<double>(mAmbientColor.y)));
        ambientColor.insert(2, QJsonValue(static_cast<double>(mAmbientColor.z)));

        ambientObject.insert("strength", static_cast<double>(mAmbientStrenght));
        ambientObject.insert("color", ambientColor);

        QJsonObject lightObject;
        QJsonArray lightColor;
        lightColor.insert(0, QJsonValue(static_cast<double>(mLightColor.x)));
        lightColor.insert(1, QJsonValue(static_cast<double>(mLightColor.y)));
        lightColor.insert(2, QJsonValue(static_cast<double>(mLightColor.z)));

        lightObject.insert("strength", static_cast<double>(mLightStrenght));
        lightObject.insert("color", lightColor);

        QJsonObject specularObject;
        specularObject.insert("strength", static_cast<double>(mSpecularStrenght));
        specularObject.insert("exponent", mSpecularExponent);

        object.insert("ambient", ambientObject);
        object.insert("light", lightObject);
        object.insert("specular", specularObject);

        return object;
    }
};
#endif // LIGHT_H
