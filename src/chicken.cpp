#include "chicken.h"
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"

using namespace Ogre;
using namespace OgreBites;

chicken::chicken()
{
}

void chicken::setupEntity(SceneManager* scnMgr, Vector3 position, const String& name  )
{
    entity = scnMgr->createEntity("chicken_body.mesh");
    entity->setCastShadows(true);
    entity->setMaterialName("Chicken_body_mat");
    sceneNode = scnMgr->getRootSceneNode()->createChildSceneNode(name);
    sceneNode->attachObject(entity);
    sceneNode->setScale(2.0f,2.0f,2.0f);
    sceneNode->setPosition(position);
    setPosition(position);

}

chicken::~chicken()
{
}
void chicken::lookAt(const Vector3& targetPoint, Node::TransformSpace relativeTo,
                    const Vector3& localDirectionVector)
{
    sceneNode->lookAt(targetPoint, relativeTo, localDirectionVector);
    setDirection(targetPoint);
}
