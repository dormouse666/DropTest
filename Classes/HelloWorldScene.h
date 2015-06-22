#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class DropItem;

class HelloWorld : public cocos2d::Layer
{
public:
    constexpr static const float DROP_INTERVAL_DEFAULT = 0.2f;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    // ここから
    HelloWorld();
    ~HelloWorld();
    
    void onEnter() override;
    void onExit() override;
    
    void entryItem();
    
    void update(float dt);
    void updateGamePlaying(float dt);
    
    float randomItemPositionX();

private:
    cocos2d::Node* _backGround;
    DropItem* _dropItem;
    float _elapse;
    float _dropInterval;
    int _itemRotate;
};

#endif // __HELLOWORLD_SCENE_H__
