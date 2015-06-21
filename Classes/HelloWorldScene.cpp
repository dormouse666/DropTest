#include "HelloWorldScene.h"
#include "DropItem.h"

USING_NS_CC;

// コンストラクタ
HelloWorld::HelloWorld()
: _backGround(nullptr)
, _dropItem(nullptr)
, _elapse(0.0f)
, _dropInterval(DROP_INTERVAL_DEFAULT)
, _itemRotate(0)
{
}

// デストラクタ
HelloWorld::~HelloWorld()
{
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// initは初期化
bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    return true;
}

// onEnterは生成
void HelloWorld::onEnter()
{
    Layer::onEnter();
    
    // 画面サイズ取得
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // Homeに戻るボタン
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    // 背景配置
    _backGround = Node::create();
    if(_backGround)
    {
        // 背景サイズとか
        _backGround->setContentSize({visibleSize.width * 0.7f, visibleSize.height * 0.6f});
        _backGround->setAnchorPoint(Point(0.5f, 0.5f));
        _backGround->setPosition(visibleSize.width / 2, visibleSize.height / 2);
        
        // 適当に色つけとく
        auto color = LayerGradient::create(Color4B(255, 255, 255, 255), Color4B(8, 8, 8, 255), Point(1, 1));
        color->setContentSize({visibleSize.width * 0.7f, visibleSize.height * 0.6f});
        _backGround->addChild(color);
        
        this->addChild(_backGround);
    }
    
    // アイテム生成
    this->entryItem();
    
    // スケジュール走らせる
    this->scheduleUpdate();
}

void HelloWorld::onExit()
{
    Layer::onExit();
}

// Homeに戻るボタン
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// 新しいdropItemを出現させる
void HelloWorld::entryItem()
{
    _dropItem = DropItem::create();
    _dropItem->setPosition(_backGround->getContentSize().width / 2, _backGround->getContentSize().height);
    _backGround->addChild(_dropItem);
    
}

void HelloWorld::update(float dt)
{
    this->updateGamePlaying(dt); //update
}

void HelloWorld::updateGamePlaying(float dt)
{
    _elapse += dt;
    
    if(_elapse >= _dropInterval) //インターバル制御
    {
        if (_dropItem)
        {
            if(_dropItem->canPlace(_dropItem, _backGround))
            {
            //下に動かす
            _dropItem->setPosition(_dropItem->getPosition().x,
                                   _dropItem->getPosition().y - 30);
            
            //回転する
            _itemRotate = _itemRotate + 20;
            _dropItem->setRotation(_itemRotate);
            }
            else
            {
                if(_dropItem)
                {
                    _dropItem->removeFromParent();
                    _dropItem = nullptr;
                }
                this->entryItem();
            }
        }
        
         _elapse = 0.0f; //戻す
    }
}
