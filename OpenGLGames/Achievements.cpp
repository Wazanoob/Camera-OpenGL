#include "Achievements.h"
#include <iostream>

Achievements::Achievements()
{
    achievementState[Achievement::CameraSwitch] = false;
}

void Achievements::onNotify(const Actor& actorP, Event event)
{
    switch (event)
    {
    case Event::ACTOR_SWITCH_CAMERA:
    {
        if (!achievementState[Achievement::CameraSwitch])
        {
            unlock(Achievement::CameraSwitch);
        }
        break;
    }
    case Event::ACTOR_ZOOM_CAMERA:
    {
        if (!achievementState[Achievement::CameraZoom])
        {
            unlock(Achievement::CameraZoom);
        }
        break;
    }
    }
}   

void Achievements::unlock(Achievement achievementP)
{
    switch (achievementP)
    {
    case Achievement::CameraSwitch:
    {
        achievementState[Achievement::CameraSwitch] = true;
        std::cout << "Achievement unlocked ! Camera Switch" << std::endl;

        break;
    }
    case Achievement::CameraZoom:
    {
        achievementState[Achievement::CameraZoom] = true;
        std::cout << "Achievement unlocked ! Zoom in & out" << std::endl;

        break;
    }
    };
}
