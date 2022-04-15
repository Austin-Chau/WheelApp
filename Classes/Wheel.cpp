//
// Created by aznch on 4/13/2022.
//

#include "Wheel.h"

#include <cmath>

static constexpr unsigned NUM_REWARDS = 8;
static constexpr float REWARD_RADIUS = 38.0f;

USING_NS_CC;

Wheel* Wheel::createWheel(cocos2d::Vec2 position)
{
    Wheel* wheel = new Wheel();
    wheel->setPosition(position);
    wheel->init();

    return wheel;
}

bool Wheel::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _rewards = std::vector<Reward>();
    currentWheelAngle = 0;
    _firstSpin = true;

    auto spinningWheel = Sprite::create("sprites/wheel_sections_8.png");

    if (spinningWheel)
    {
        spinningWheel->setPosition(Vec2::ZERO);
        spinningWheel->setScale(0.5f, 0.5f);
        this->addChild(spinningWheel, 0);
    }

    addSpriteToRewards("Life", "30m", "sprites/heart.png", 0.2f);
    addSpriteToRewards("Brush", "x3", "sprites/brush.png", 0.1f);
    addSpriteToRewards("Gems", "x35", "sprites/gem.png", 0.1f);
    addSpriteToRewards("Hammer", "x3", "sprites/hammer.png", 0.1f);
    addSpriteToRewards("Coin", "x750", "sprites/coin.png", 0.05f);
    addSpriteToRewards("Brush", "x1", "sprites/brush.png", 0.2f);
    addSpriteToRewards("Gems", "x75", "sprites/gem.png", 0.05f);
    addSpriteToRewards("Hammer", "x1", "sprites/hammer.png", 0.2f);


    return true;
}

void Wheel::addSpriteToRewards(std::string name, std::string quantity, std::string pathToSprite, float dropChance)
{
    // Only add to list if not full
    if(_rewards.size() < NUM_REWARDS) {

        auto sprite = Sprite::create(pathToSprite);
        auto rewardInd = _rewards.size();
        if (sprite) {
            _rewards.emplace_back(name, quantity, sprite, dropChance);
        }
        this->addChild(sprite, _rewards.size());
        sprite->setScale(0.5f, 0.5f);

        // Add label
        auto rewardLabel = Label::createWithSystemFont(quantity, "", 16, Size::ZERO, TextHAlignment::RIGHT, TextVAlignment::CENTER);
        rewardLabel->enableOutline(Color4B(157,99,38,100), 3);
        rewardLabel->setPosition(Vec2(20, 0));
        sprite->addChild(rewardLabel, 1);

        // Place reward in the correct spots on the wheel
        auto angle = (rewardInd * ((MATH_PIOVER2 * 4) / NUM_REWARDS)) + (MATH_PIOVER2 / 4) ;
        auto pos = Vec2(std::cos(angle) * REWARD_RADIUS, std::sin(angle) * REWARD_RADIUS);
        sprite->setPosition(pos);
        // Rotate the sprite towards the center
        sprite->setRotation(90 - MATH_RAD_TO_DEG(angle));
    }
}

Reward* Wheel::spinWheel(CallFunc* isFinished)
{
    auto spinVal = random(0.0f, 1.0f);
    auto rewardIndex = 0;

    while(spinVal > 0.0f && rewardIndex < _rewards.size())
    {
        spinVal -= _rewards[rewardIndex].weight;
        if(spinVal > 0.0f) {
            rewardIndex++;
        }
    }
    log("Got %i: %s", rewardIndex, _rewards[rewardIndex].name.c_str());

    // Figure out amount of degrees to rotate based on reward.
    // The image starts in between cells so we need to add 22.5 to land on the right wedge
    // We subtract 90 as our 0 degrees starts on the 3'o'clock position but we want to land on the top
    float angleOffset = -currentWheelAngle;
    if(_firstSpin)
    {
        angleOffset += 22.5f - 90;
        _firstSpin = false;
    }
    auto angleOfReward = (rewardIndex * (360.0f / NUM_REWARDS)) + angleOffset;

    // Make sure angle is positive
    angleOfReward += 360;
    if(angleOfReward >= 360)
    {
        angleOfReward -= 360;
    }
    currentWheelAngle = (rewardIndex * (360 / NUM_REWARDS)) % 360;

    auto fastSpin = RotateBy::create(4, 1440);
    auto slowSpin = RotateBy::create(2 * (angleOfReward / 360), angleOfReward);
    auto seq = Sequence::create(fastSpin, slowSpin, isFinished, nullptr);


    this->runAction(seq);

    return new Reward(_rewards[rewardIndex]);
}
