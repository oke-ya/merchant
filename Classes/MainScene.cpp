//
//  MainScene.cpp
//  merchant
//
//  Created by Atsushi Yoshida on 2016/04/30.
//
//

#include "MainScene.h"

bool MainScene::init()
{
    auto layout = Layout::create();
    layout->setContentSize(Director::getInstance()->getWinSize());
    addChild(layout);

    auto start = getChildByName<ImageView*>("elrukh");
    start->setTouchEnabled(true);
    start->addTouchEventListener([&](Ref* ref, Widget::TouchEventType eventType){
        if(_moving){
            return;
        }
        auto node = static_cast<ImageView*>(ref);
        switch(eventType){
            case Widget::TouchEventType::BEGAN:{
                swipeStart(node->getPosition());
                break;
            }
            case Widget::TouchEventType::MOVED:{
                swiping(node->getParent()->convertToWorldSpace(node->getTouchMovePosition()));
                break;
            }
            case Widget::TouchEventType::CANCELED:
            case Widget::TouchEventType::ENDED:{
                swipeFinish();
                break;
            }
        }
    });
    return true;
}

void MainScene::swipeStart(const Vec2 pos)
{
    _points.clear();
    _points.push_back(pos);
    _swipeStarted = true;
}

void MainScene::swiping(const Vec2 pos)
{
    if(pos == Vec2::ZERO){
        return;
    }
    auto line = DrawNode::create();
    line->drawLine(_points.back(), pos, Color4F::WHITE);
    _lines.push_back(line);
    addChild(line);
    _points.push_back(pos);
}

void MainScene::swipeFinish()
{
    for(auto line: _lines){
        line->removeFromParent();
    }
    _lines.clear();
    moveNextPoint();
    _moving = true;
}

void MainScene::moveNextPoint()
{
    if(_points.empty()){
        _moving = false;
        return;
    }
    auto pos = _points.front();
    auto character = getChildByName<ImageView*>("elrukh");;
    auto move = MoveTo::create(0.1f, pos);
    auto fun = CallFunc::create([&](){ moveNextPoint(); });
    _points.erase(_points.begin());
    character->runAction(Sequence::create(move, fun, nullptr));
}