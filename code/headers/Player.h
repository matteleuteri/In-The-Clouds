#ifndef _PLAYER
#define _PLAYER

#define PI 3.141592653589793238463f

#include <stdint.h>
#include <d2d1.h>
#include <memory>
#include "GameObject.h"

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
    // ID2D1Bitmap* bitmap;
    // float x;
    // float y;
    float angle; 
    int width;
    int height;
    bool isActive;
    float leftSpeed;
    float rightSpeed;
    float upSpeed;
    float downSpeed;
    float speedScale;// speed boost modifier / scaler/ thingy
    bool goingRight;
    bool goingLeft;
    bool goingUp;
    bool goingDown;

    Player::Player(ID2D1Bitmap *bitmap, float x, float y);
    void Player::update(int64_t timeElapsed, HWND hwnd);
    void Player::pointPlayerTowards(POINT mousePosition);
    void Player::moveTowardsZero(DIRECTION direction);   
    void Player::flipBitmap();
};

#endif