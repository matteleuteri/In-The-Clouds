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
#include <array>

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
    float width;
    float height;
    float ySpeed;
    bool isActive;
    bool isInAir;

    int32_t timeInAir;
    int32_t immune;
    WorldChunk *chunkCurrentlyOn;

    Animation *jumpAnimation;
    void Player::fallOff();
    void Player::setPosition(float x2, float y2);
    Player::Player(AnimationController *animationController, float x, float y, float xSpeed);
    void Player::jump();
    void Player::update(int32_t timeElapsed);
    void Player::landOn(WorldChunk *wc, float newX, float newY);
    std::array<float, 2> Player::getAbsoluteCoordinates();
};

#endif