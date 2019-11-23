#include "gui.h"
#include <QJsonArray>
#include "Factories/guifactory.h"
GUI::GUI()
{

}

GUI::GUI(gsl::Vector2D position, gsl::Vector2D scale) : position_(position), scale_(scale){}

GUI::GUI(QJsonObject Json)
{
    fromJson(Json);
}

QJsonObject GUI::toJson()
{
    QJsonObject object;
    QJsonArray positionArray;
    positionArray.insert(0,static_cast<double>(position_.x));
    positionArray.insert(1,static_cast<double>(position_.y));
    QJsonArray scaleArray;
    scaleArray.insert(0, static_cast<double>(scale_.x));
    scaleArray.insert(1, static_cast<double>(scale_.y));
    object.insert("position", positionArray);
    object.insert("scale", scaleArray);
    return object;
}

void GUI::fromJson(QJsonObject Json)
{
    QJsonArray positionArray = Json.take("position").toArray();
    position_.x = static_cast<float>(positionArray.at(0).toDouble());
    position_.y = static_cast<float>(positionArray.at(1).toDouble());

    QJsonArray scaleArray = Json.take("scale").toArray();
    scale_.x = static_cast<float>(scaleArray.at(0).toDouble());
    scale_.y = static_cast<float>(scaleArray.at(1).toDouble());

    VAO_ = GUIFactory::get()->createGUI().VAO_;

}
