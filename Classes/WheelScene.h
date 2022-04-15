//
// Created by Austin Chau on 4/12/2022.
//

#ifndef PROJ_ANDROID_WHEELSCENE_H
#define PROJ_ANDROID_WHEELSCENE_H

#include "cocos2d.h"
#include "Wheel.h"

class WheelScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(WheelScene);

private:
    void spinWheel();
    void claimReward();

    Wheel* _wheel;
    Reward* _claimedReward;
    cocos2d::Menu* _menu;
    cocos2d::Label* _rewardLabel;
    cocos2d::Sprite* spinningWheel;
};

#endif //PROJ_ANDROID_WHEELSCENE_H
