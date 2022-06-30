#ifndef _PLAYER
#define _PLAYER

#define PI 3.141592653589793238463f

#include <stdint.h>
#include <d2d1.h>
#include <memory>
#include <map>
#include "GameObject.h"
#include "WorldChunk.h"
#include "AnimationController.h"
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
    // float angle; 
    float width;
    float height;
    bool isActive;
    // float upSpeed;
    // float downSpeed;
    // float leftSpeed;
    // float rightSpeed;
    // float speedScale;
    // bool goingRight;
    // bool goingLeft;
    float ySpeed;
    bool isInAir;
    int32_t inAirStartTime;

    int32_t immune;
    WorldChunk *chunkCurrentlyOn;

    Animation *jumpAnimation;

    Player::Player(AnimationController *animationController, float x, float y);
    void Player::jump();
    void Player::update(int32_t timeElapsed, int32_t currentTime);
    // void Player::moveTowardsZero(DIRECTION direction);   
};

#endif