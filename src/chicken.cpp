#include "chicken.h"

chicken::chicken()
{
}

void chicken::setupEntity(SceneManager* scnMgr, Vector3 position )
{
    entity = scnMgr->createEntity("chicken_body.mesh");
    entity->setCastShadows(true);
    entity->setMaterialName("Chicken_body_mat");
    sceneNode = scnMgr->getRootSceneNode()->createChildSceneNode("ChickenNode");
    sceneNode->attachObject(entity);
    sceneNode->setScale(1.0f,1.0f,1.0f);
    sceneNode->setPosition(position);

}

chicken::~chicken()
{
}
