#include "npc.h"

Npc::Npc() {}

Npc::Npc(BSplineCurve* Curve) : bSplineCurve(Curve) {}


QJsonObject Npc::toJson()
{
}

void Npc::fromJson(QJsonObject Json)
{
}