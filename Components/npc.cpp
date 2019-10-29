#include "npc.h"

//Npc::Npc()
//{

//}

void Npc::patrol()
{
    position = gsl::Vector3D(0); //Byttes ut med deBoor(t)

    if(event == NPCevents::ENDPOINT_ARRIVED)
    {
        notify(static_cast<int>(event));
        state = NPCstates::LEARN;
    }
    if(event == NPCevents::ITEM_TAKEN)
        notify(0); // Hvilket item som ble tatt
    if(event == NPCevents::PLAYER_DETECTED)
    {
        notify(0); //Player Position
        state = NPCstates::LEARN;
    }

//                if (endpoint arrived)
//        notify(endpoint_arrived)
//                npc_state = LEARN
//                if (item collected)
//                notify(control_point_index)
//                if (player detected)
//                notify(player_position)
//                npc_state = LEARN
//                else if (obstacle detected)
//                notify(obstacle_position, control_point_index)
//                npc_state = LEARN
//                else
    //                previous_position = position
}

void Npc::notify(int notification)
{

}
