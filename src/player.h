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

        int getXPos() { return xPos; }
        void setXPos(int val) { xPos = val; }
        int getYPos() { return yPos; }
        void setYPos(int val) { yPos = val; }
        Vector3 getDirection() { return direction; }
        void setDirection(Vector3 val) { direction = val; }

    protected:
        int xPos;
        int yPos;
        Vector3 direction;

    private:

};

#endif // PLAYER_H
