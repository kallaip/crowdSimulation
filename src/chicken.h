#ifndef CHICKEN_H
#define CHICKEN_H

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"

#include "player.h"

using namespace Ogre;
using namespace OgreBites;

class chicken : public player
{
    public:
        chicken();
        virtual ~chicken();
        void setupEntity(SceneManager* scnMgr, Vector3 position );

    protected:

    private:
    Entity* entity;
    SceneNode* sceneNode;
};

#endif // CHICKEN_H
