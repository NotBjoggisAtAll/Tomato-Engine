#include "npc.h"

Npc::Npc() {}

Npc::Npc(BSplineCurve* Curve) : bSplineCurve(Curve) {}


QJsonObject Npc::toJson()
{
    QJsonObject object;
    object.insert("speed", static_cast<double>(speed_));
    object.insert("state", static_cast<int>(state_));
    return object;
}

void Npc::fromJson(QJsonObject Json)
{
    speed_ = static_cast<float>(Json.take("speed").toDouble());
    state_ = static_cast<NPCstates>(Json.take("state").toInt());
}
