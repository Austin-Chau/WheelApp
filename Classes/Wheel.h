//
// Created by aznch on 4/13/2022.
//

#ifndef PROJ_ANDROID_WHEEL_H
#define PROJ_ANDROID_WHEEL_H

#include "cocos2d.h"

struct Reward {
    std::string name;
    std::string quantity; // This would be better as a abstractable quantifier
    cocos2d::Sprite* sprite;
    float weight;

    Reward(std::string name_, std::string quantity_, cocos2d::Sprite* sprite_, float weight_) :
        name(name_),
        quantity(quantity_),
        sprite(sprite_),
        weight(weight_) {}

    Reward(const Reward& toCopy) :
        name(toCopy.name),
        quantity(toCopy.quantity),
        sprite(toCopy.sprite),
        weight(toCopy.weight) {}
};

class Wheel : public cocos2d::Sprite {
public:
    static Wheel* createWheel(cocos2d::Vec2 position);

    virtual bool init();

    Reward* spinWheel(cocos2d::CallFunc* isFinished);

private:
    void addSpriteToRewards(std::string name, std::string quantity, std::string pathToSprite, float dropChance);

    int currentWheelAngle;
    std::vector<Reward> _rewards;
    bool _firstSpin;

};


#endif //PROJ_ANDROID_WHEEL_H
