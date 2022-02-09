#ifndef CHICKEN_H
#define CHICKEN_H

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"
#include "OgreNode.h"
#include "player.h"

using namespace Ogre;
using namespace OgreBites;

class chicken : public player
{
    public:
    chicken();
    virtual ~chicken();
    void setupEntity(SceneManager* scnMgr, Vector3 position, const String& name );
    void lookAt(const Vector3& targetPoint, Node::TransformSpace relativeTo = Node::TransformSpace::TS_PARENT,
                const Vector3& localDirectionVector = Vector3::UNIT_X);
    void move(float elapsedTime);
    protected:

    private:
    Entity* entity;
    SceneNode* sceneNode;
};

#endif // CHICKEN_H
