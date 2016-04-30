//
//  MainScene.h
//  merchant
//
//  Created by Atsushi Yoshida on 2016/04/30.
//
//

#ifndef __merchant__MainScene__
#define __merchant__MainScene__

#include "BaseScene.h"

using namespace cocos2d;

class MainScene : public BaseScene<MainScene>
{
public:
    bool init();
private:
    void swipeStart(const Vec2 pos);
    void swiping(const Vec2 pos);
    void swipeFinish();
    void moveNextPoint();
    std::vector<Vec2> _points;
    std::vector<DrawNode*> _lines;
    bool _swipeStarted{ false };
    bool _moving{ false };
};

#endif /* defined(__merchant__MainScene__) */
