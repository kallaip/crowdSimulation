/*-------------------------------------------------------------------------

-------------------------------------------------------------------------*/
#include <exception>
#include <iostream>

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"

#include "defaults.h"

using namespace Ogre;
using namespace OgreBites;

class crowdSimulation:
        public ApplicationContext,
        public InputListener
{
public:
    crowdSimulation();
    virtual ~crowdSimulation();

    void setup();
    bool keyPressed(const KeyboardEvent& evt);
};


crowdSimulation::crowdSimulation()
    : ApplicationContext("crowdSimulation")
{
}


crowdSimulation::~crowdSimulation()
{
}

void crowdSimulation::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    Root* root = getRoot();
    SceneManager* scnMgr = root->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    Camera* cam = scnMgr->createCamera("myCam");

    //isometric camera settings
    camNode->setPosition(CAM_X, CAM_Y, CAM_Z);
    camNode->lookAt(Vector3(GROUND_X/2, 0, GROUND_Z/2), Node::TransformSpace::TS_WORLD);
    cam->setProjectionType(ProjectionType::PT_ORTHOGRAPHIC);
    cam->setOrthoWindow(GROUND_X*0.6f, GROUND_Z*0.6f);
    cam->setNearClipDistance(0.01);
    camNode->attachObject(cam);

    Viewport* vp = getRenderWindow()->addViewport(cam);
    vp->setBackgroundColour(ColourValue(0.4, 0.7, 0.7));

    cam->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));

    scnMgr->setAmbientLight(ColourValue(0.8, 0.8, 0.8));
    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
   // scnMgr->setSkyDome(true, "Examples/CloudySky", 10, 8);

    Entity* chickenEntity = scnMgr->createEntity("chicken_body.mesh");
    chickenEntity->setCastShadows(true);
    chickenEntity->setMaterialName("Chicken_body_mat");
    SceneNode* cn = scnMgr->getRootSceneNode()->createChildSceneNode("ChickenNode");
    cn->attachObject(chickenEntity);
    cn->setScale(1.0f,1.0f,1.0f);
    cn->setPosition(Vector3(GROUND_X/2,1,GROUND_Z/2));
    Plane plane(Vector3::UNIT_Y, 0);

    MeshManager::getSingleton().createPlane(
            "ground", RGN_DEFAULT,
            plane,
            GROUND_X, GROUND_Z, 10, 10,
            true,
            1, 5, 5,
            Vector3::UNIT_Z);

    Entity* groundEntity = scnMgr->createEntity("ground");
    SceneNode* gn = scnMgr->getRootSceneNode()->createChildSceneNode("groundNode");
    gn->attachObject(groundEntity);
    gn->setPosition(Vector3(GROUND_X/2, 0, GROUND_Z/2));
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("sand");

//==================================
/*    Light* spotLight = scnMgr->createLight("SpotLight");
    spotLight->setDiffuseColour(0, 0, 1.0);
    spotLight->setSpecularColour(0, 0, 1.0);
    spotLight->setType(Light::LT_SPOTLIGHT);
    SceneNode* spotLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    spotLightNode->attachObject(spotLight);
    spotLightNode->setDirection(-1, -1, 0);
    spotLightNode->setPosition(Vector3(GROUND_X/2, GROUND_X*2, GROUND_Z/2));
    spotLight->setSpotlightRange(Degree(35), Degree(50));
*/
    Light* directionalLight = scnMgr->createLight("DirectionalLight");
    directionalLight->setType(Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour(ColourValue(0.4, 0.3, 0.3));
    directionalLight->setSpecularColour(ColourValue(0.4, 0.5, 0.5));
    SceneNode* directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    directionalLightNode->attachObject(directionalLight);
    directionalLightNode->setDirection(Vector3(0, -1, 1));

    Light* pointLight = scnMgr->createLight("PointLight");
    pointLight->setType(Light::LT_POINT);
    pointLight->setDiffuseColour(0.3, 0.3, 0.3);
    pointLight->setSpecularColour(0.3, 0.3, 0.3);
    SceneNode* pointLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    pointLightNode->attachObject(pointLight);
    pointLightNode->setPosition(Vector3(0, 150, 250));

}


bool crowdSimulation::keyPressed(const KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    return true;
}


int main(int argc, char **argv)
{
    try
    {
        crowdSimulation app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
