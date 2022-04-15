//
// Created by Austin Chau on 4/12/2022.
//


#include "WheelScene.h"

USING_NS_CC;

Scene* WheelScene::createScene()
{
    return WheelScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool WheelScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(WheelScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    auto spinButton = MenuItemImage::create(
            "sprites/spin_button.png",
            "sprites/spin_button.png",
            [&](Ref* ref){spinWheel(); });

    if (spinButton == nullptr ||
        spinButton->getContentSize().width <= 0 ||
        spinButton->getContentSize().height <= 0)
    {
        problemLoading("'sprites/spin_button.png'");
    }
    else
    {
        float x = visibleSize.width/2 + origin.x;
        float y = origin.y + visibleSize.height/4;
        spinButton->setScale(0.5f);
        spinButton->setPosition(Vec2(x,y));
        spinButton->setAnchorPoint(Vec2(0.5f, 0.5f));

        auto playLabel = Label::createWithSystemFont("Play On", "", 28, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
        auto imageSize = spinButton->getNormalImage()->getBoundingBox().size;
        // For some reason, button images are anchored at 0,0 by default rather than 0.5f, 0.5f...
        playLabel->setPosition(Vec2(imageSize.width / 2, imageSize.height / 2));
        playLabel->enableOutline(Color4B(83,152,45,100), 2);
        spinButton->addChild(playLabel);
    }

    // For sake of time we'll do the same as above, but we can probably put this in some ButtonGenerator class
    auto claimButton = MenuItemImage::create(
            "sprites/spin_button.png",
            "sprites/spin_button.png",
            [&](Ref* ref){ claimReward(); });

    if (claimButton == nullptr ||
        claimButton->getContentSize().width <= 0 ||
        claimButton->getContentSize().height <= 0)
    {
        problemLoading("'sprites/spin_button.png'");
    }
    else
    {
        float x = visibleSize.width/2 + origin.x;
        float y = origin.y + visibleSize.height/4;
        claimButton->setScale(0.5f);
        claimButton->setPosition(Vec2(x,y));
        claimButton->setAnchorPoint(Vec2(0.5f, 0.5f));

        auto claimLabel = Label::createWithSystemFont("Claim", "", 28, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
        auto imageSize = claimButton->getNormalImage()->getBoundingBox().size;
        // For some reason, button images are anchored at 0,0 by default rather than 0.5f, 0.5f...
        claimLabel->setPosition(Vec2(imageSize.width / 2, imageSize.height / 2));
        claimLabel->enableOutline(Color4B(83,152,45,100), 2);
        claimButton->addChild(claimLabel);
    }

    _menu = Menu::create(closeItem, NULL);
    _menu->setPosition(Vec2::ZERO);
    this->addChild(_menu, 1);
    _menu->addChild(spinButton, -1, "spin");
    _menu->addChild(claimButton, 1, "claim");
    claimButton->setVisible(false);

    _rewardLabel = Label::createWithSystemFont("Got ", "", 16, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
    // For some reason, button images are anchored at 0,0 by default rather than 0.5f, 0.5f...
    _rewardLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - 50));
    _rewardLabel->enableOutline(Color4B::BLACK, 2);
    _rewardLabel->setVisible(false);
    this->addChild(_rewardLabel, 100);

    // Make Border
    auto centerOfScreen = Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y);

    auto background = Sprite::create("background.jpg");

    if (background) {
        background->setPosition(centerOfScreen);
        this->addChild(background, -5000);
    }

    auto wheelArrow = Sprite::create("sprites/wheel_arrow.png");

    if (wheelArrow)
    {
        wheelArrow->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y + 53));
        wheelArrow->setScale(0.495f, 0.495f);
        this->addChild(wheelArrow, 5);
    }

    _wheel = Wheel::createWheel(centerOfScreen);
    this->addChild(_wheel, 0);

    auto wheelBorder = Sprite::create("sprites/wheel_border.png");

    if (wheelBorder)
    {
        wheelBorder->setPosition(centerOfScreen);
        wheelBorder->setScale(0.495f, 0.495f);
        this->addChild(wheelBorder, 1);
    }

    _wheel = Wheel::createWheel(centerOfScreen);
    this->addChild(_wheel, 0);

    return true;
}

void WheelScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

void WheelScene::spinWheel() {
    auto spinButton = _menu->getChildByName<MenuItemImage*>("spin");
    auto claimButton = _menu->getChildByName<MenuItemImage*>("claim");
    spinButton->setVisible(false);
    auto setMenuVisible = CallFunc::create([&, claimButton](){
        _rewardLabel->setVisible(true);
        claimButton->setVisible(true);
    });
    _claimedReward = _wheel->spinWheel(setMenuVisible);
    _rewardLabel->setString("Got " + _claimedReward->name + " " + _claimedReward->quantity +"!");
}

void WheelScene::claimReward() {
    log("Reward claimed %s", _claimedReward->name.c_str());

    auto spinButton = _menu->getChildByName<MenuItemImage*>("spin");
    auto claimButton = _menu->getChildByName<MenuItemImage*>("claim");

    spinButton->setVisible(true);
    claimButton->setVisible(false);
    _rewardLabel->setVisible(false);
}
