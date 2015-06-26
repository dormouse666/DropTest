#include "HelloWorldScene.h"
#include "DropItem.h"

USING_NS_CC;

// コンストラクタ
HelloWorld::HelloWorld()
: _backGround(nullptr)
, _dropItem(nullptr)
, _elapseEntry(0.0f)
, _entryInterval(ENTRY_INTERVAL_DEFAULT)
{
    if(_dropItemList.size() != 0)
    {
        for(auto a : _dropItemList)
        {
            this->removeChild(a);
        }
    }
    _dropItemList.clear();
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
    _dropItem->setPosition(randomItemPositionX(), _backGround->getContentSize().height);
    _backGround->addChild(_dropItem);
    
    _dropItem->setTag(_dropItemList.size()); //tag付け
    _dropItemList.push_back(_dropItem); //格納しておく
}

// dropItem出現位置をランダムに
float HelloWorld::randomItemPositionX()
{
    std::random_device rnd; //乱数の生成
    std::mt19937 mt(rnd()); //乱数生成器
    
    auto w = _backGround->getContentSize().width;
    
    auto itemPositionX = w / 2; //とりあえず真ん中
    int i = mt() % static_cast<int>(w); //背景のwidthで割った余り
    if(i <= w)
    {
        // dropItemの対角線の半分バッファを取りたい
        float diagonal = _dropItem->getDiagonal(_dropItem) / 2;
        
        // 出現範囲
        float minX = _backGround->getPositionX() - _backGround->getContentSize().width/2 + diagonal;
        float maxX = _backGround->getPositionX() + _backGround->getContentSize().width/2 - diagonal;
        
        if(minX >= i)
        {
            itemPositionX = i + diagonal;
        }
        else if(maxX <= i)
        {
            itemPositionX = i - diagonal;
        }
        else
        {
            itemPositionX = i;
        }
    }
    
    return itemPositionX;
}

void HelloWorld::update(float dt)
{
    this->updateGamePlaying(dt); //update
}

void HelloWorld::updateGamePlaying(float dt)
{
    _elapseEntry += dt;
    
    // 移動
    for(auto i = 0; i < _dropItemList.size(); i++)
    {
        if (_dropItemList[i])
        {
            CCLOG("tag: %d", _dropItemList[i]->getTag());
            CCLOG("i: %d", i);
            
            if(_dropItemList[i]->canPlace(_dropItemList[i], _backGround))
            {
                //下に動かす
                _dropItemList[i]->setPosition(_dropItemList[i]->getPosition().x,
                                              _dropItemList[i]->getPosition().y - 1);
            }
            else
            {
                if(_dropItemList[i])
                {
                    _dropItemList[i]->removeFromParent();
                    _dropItemList[i] = nullptr;
                }
            }
        }
    }
    
    // 時間経過で新規item出現
    if(_elapseEntry >= _entryInterval) //インターバル制御
    {
        this->entryItem();
        _elapseEntry = 0.0f; //経過時間戻す
    }
}
