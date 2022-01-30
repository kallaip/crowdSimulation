#ifndef PLAYER_H
#define PLAYER_H

#include <exception>
#include <iostream>

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"

using namespace Ogre;
using namespace OgreBites;

class player
{
    public:
        player();
        virtual ~player();

        Vector3 getPosition() { return position; }
        void setPosition(Vector3 val) { position = val; }

        Vector3 getDirection() { return direction; }
        void setDirection(Vector3 val) { direction = val; }

    protected:
        Vector3 position;
        Vector3 direction;

    private:

};

#endif // PLAYER_H
