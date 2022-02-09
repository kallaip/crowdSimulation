#include "player.h"
#include "defaults.h"


using namespace Ogre;
using namespace OgreBites;

player::player()
{

}

player::~player()
{
}

void player::move(float elapsedTime)
{
    // handle bouncing on boundaries
    if(position.x < BOUNDARY_X_N || position.x > BOUNDARY_X)
    {
        direction.x*=-1;
        position += direction*0.001f; //avoid infinite loops
    }
    if(position.z < BOUNDARY_Z_N || position.z > BOUNDARY_Z)
    {
        direction.z*=-1;
        position += direction*0.001f;
    }
    // move
    position += direction.normalisedCopy() * elapsedTime * velocity;

}
