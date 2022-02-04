/*-------------------------------------------------------------------------

-------------------------------------------------------------------------*/
#include <exception>
#include <iostream>
#include <vector>
#include <time.h>
#include <string>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"

#include "defaults.h"
#include "chicken.h"

using namespace std;
using namespace Ogre;
using namespace OgreBites;

class crowdSimulation:
        public ApplicationContext,
        public InputListener
{
public:
    crowdSimulation();
    virtual ~crowdSimulation();
    Vector3 testVector;
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


    int chicken_num = 10;
    std::vector<chicken*> chickens((size_t) chicken_num);
    time_t tm;
    int x,z;

    for(int i=0; i<chicken_num; i++)
    {
        srand(time(&tm)+x*z);
        x = rand() % GROUND_X;
        z = rand() % GROUND_Z;
        cout << "Chicken_" << i << ": ("  << x << ", " << z << ") " << endl;

        chickens[i] = new chicken();
        String chicken_name = "chicken_";
        chicken_name.append(to_string(i));
        chickens[i]->setupEntity(scnMgr, Vector3( x, 1.4f, z ), chicken_name.c_str());

        if (i>1)
        {
           srand(time(&tm));
           int l = rand() % i;
           chickens[i]->lookAt(chickens[l]->getPosition());
        }
        sleep(0.16846934);
    }

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

