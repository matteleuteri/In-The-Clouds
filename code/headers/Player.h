#ifndef _PLAYER
#define _PLAYER

#define PI 3.141592653589793238463f

#include <stdint.h>
#include <d2d1.h>
#include <memory>
#include "GameObject.h"
#include "WorldChunk.h"
#include <vector>

enum DIRECTION
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class Player: public GameObject
{
public:
    float angle; 
    float width;
    float height;
    bool isActive;
    float upSpeed;
    float downSpeed;
    float leftSpeed;
    float rightSpeed;
    float speedScale;
    bool goingRight;
    bool goingLeft;
    
    bool isInAir;
    int32_t inAirStartTime;

    int32_t immune;
    WorldChunk *chunkCurrentlyOn;

    Player::Player(Animation *animation, float x, float y);
    void Player::doGravity(int32_t currentTime);
    void Player::jump();
    void Player::update(int32_t timeElapsed);
    void Player::moveTowardsZero(DIRECTION direction);   
};

#endif