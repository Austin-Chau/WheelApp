//
// Created by Austin Chau on 4/14/2022.
//

#include "gtest/gtest.h"
#include "cocos2d.h"

#include "../../../../../Classes/Wheel.h"

#include <map>

class WheelTest : public ::testing::Test{
protected:
    Wheel* wheel;

    void SetUp() override
    {
        wheel = Wheel::createWheel(cocos2d::Vec2::ZERO);
    }
};

TEST_F(WheelTest, spinThousandWheels)
{
    std::map<std::string, unsigned> rewardsResult;
    for(int i = 0; i < 1000; i++)
    {
        auto reward = wheel->spinWheel(nullptr);

        rewardsResult[reward->name + reward->quantity]++;
    }

    std::cout << "Occurrences of rewards in 1000" << std::endl;
    for(auto result : rewardsResult )
    {
        std::cout << result.first << "= " << result.second << std::endl;
    }
}