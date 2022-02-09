#include "chicken.h"
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"
#include "defaults.h"
#include "OgreNode.h"

using namespace Ogre;
using namespace OgreBites;

chicken::chicken()
{
}

void chicken::setupEntity(SceneManager* scnMgr, Vector3 pos, const String& name  )
{
    entity = scnMgr->createEntity("chicken_body.mesh");
    entity->setCastShadows(true);
    entity->setMaterialName("Chicken_body_mat");
    sceneNode = scnMgr->getRootSceneNode()->createChildSceneNode(name);
    sceneNode->attachObject(entity);
    sceneNode->setScale(2.0f,2.0f,2.0f);
    sceneNode->setPosition(pos);
    setPosition(pos);

}

chicken::~chicken()
{
}
void chicken::lookAt(const Vector3& targetPoint, Node::TransformSpace relativeTo,
                    const Vector3& localDirectionVector)
{
    sceneNode->lookAt(targetPoint, relativeTo, localDirectionVector);
    setDirection( Vector3 (targetPoint - position).normalisedCopy());
}

void chicken::move(float elapsedTime)
{
    player::move(elapsedTime);
    sceneNode->setDirection(direction,Node::TS_WORLD, Vector3::UNIT_X);
    sceneNode->setPosition(position);
}
