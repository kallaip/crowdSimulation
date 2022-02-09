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

        float getVelocity() { return velocity; }
        void setVelocity(float val) { velocity = val; }

        void move(float elapsedTime);

    protected:
        Vector3 position = Vector3::ZERO;
        Vector3 direction = Vector3::ZERO;
        float velocity = 0.0f;


    private:

};

#endif // PLAYER_H
