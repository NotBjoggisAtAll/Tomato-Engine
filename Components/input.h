#ifndef INPUT_H
#define INPUT_H

#include "component.h"

struct Input : public Component
{
    Input();
    Input(bool isControlable);
    Input(QJsonObject Json);
    QJsonObject toJson() override;
    void fromJson(QJsonObject Json) override;

    bool isControllable = true;
};

#endif // INPUT_H
