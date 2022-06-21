#ifndef _PLAYER
#define _PLAYER

#define PI 3.141592653589793238463f

#include <stdint.h>
#include <d2d1.h>
#include <memory>
#include "GameObject.h"
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
    float leftSpeed;
    float rightSpeed;
    float speedScale;
    bool goingRight;
    bool goingLeft;
    bool onPlatform;
    bool isInAir;
    bool immune;

    Player::Player(Animation *animation, float x, float y);
    void Player::doGravity();
    void Player::jump();
    void Player::update(int64_t timeElapsed, HWND hwnd);
    void Player::setCollisionImmunity(int64_t startTime);
    void Player::pointPlayerTowards(POINT mousePosition);
    void Player::moveTowardsZero(DIRECTION direction);   
};

#endif