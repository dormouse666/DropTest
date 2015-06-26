//
//  DropItem.cpp
//  dormouseTest
//
//  Created by dormouse666 on 2015/06/21.
//
//

#include "DropItem.h"

USING_NS_CC;

bool DropItem::init()
{
    if (!Node::init()) {
        return false;
    }
    
    return true;
}

DropItem::DropItem()
: _spr(nullptr)
, _itemRotate(0)
, _elapseRotate(0.0f)
, _rotateInterval(ROTATE_INTERVAL_DEFAULT)
{
}

DropItem::~DropItem()
{
}

void DropItem::onEnter()
{
    Node::onEnter();

    // アイテムカラーをランダムにしてセット
    setItemType(randomItemColor());
    
    // スケジュール走らせる
    this->scheduleUpdate();
}
void DropItem::onExit()
{
    Node::onExit();
}

DropItem::ColorType DropItem::randomItemColor()
{
    std::random_device rnd; //乱数の生成
    std::mt19937 mt(rnd()); //乱数生成器
    
    std::vector<DropItem::ColorType> colorList
    {
        BLUE,
        RED,
        BLACK,
        GREEN,
        ORANGE,
        PURPLE,
        YELLOW
    };
    
    auto color = BLUE;
    int i = mt() % colorList.size(); //リスト数で割った余り
    if(i <= colorList.size())
    {
        color = colorList[i];
    }
    
    return color;
}

void DropItem::setItemType(ColorType type)
{
    // テーブル化
    static std::map<ColorType, const char*> imgPathTbl = {
        {BLUE, "block_blue.png"},
        {RED, "block_red.png"},
        {BLACK, "block_black.png"},
        {GREEN, "block_green.png"},
        {ORANGE, "block_orange.png"},
        {PURPLE, "block_purple.png"},
        {YELLOW, "block_yellow.png"},
    };
    
    // 要素チェック
    if(imgPathTbl.find(type) == imgPathTbl.end())
    {
        return;
    }
    
    // 生成
    _spr = Sprite::create(imgPathTbl[type]);
    if(_spr)
    {
        this->addChild(_spr);
        
        // nodeのサイズを合わせる
        this->setContentSize(_spr->getContentSize());
    }
}

// 動かせるか判定
bool DropItem::canPlace(DropItem* dropItem, cocos2d::Node* backGround)
{
    // 親の座標に変換
    auto itemPos = backGround->convertToWorldSpace(dropItem->getPosition());
    
    // dropItemの対角線の半分バッファを取りたい
    float diagonal = getDiagonal(dropItem) / 2;
    
    // 動かせる範囲
    float minX = backGround->getPositionX() - backGround->getContentSize().width/2 + diagonal;
    float maxX = backGround->getPositionX() + backGround->getContentSize().width/2 - diagonal;
    float minY = backGround->getPositionY() - backGround->getContentSize().height/2 + diagonal;
    //auto maxY = backGround->getPositionY() + backGround->getContentSize().height/2;
    
    if(itemPos.x < minX || itemPos.x >= maxX || itemPos.y < minY)
    {
        return false;
    }
    
    return true;
}

// 傾き設定
void DropItem::setItemRotate(int rotate)
{
    _itemRotate = rotate;
    _spr->setRotation(_itemRotate);
}

int DropItem::getItemRotate()
{
    return _itemRotate;
}

void DropItem::update(float dt)
{
    _elapseRotate += dt;
    
    if(_elapseRotate >= _rotateInterval) //インターバル制御
    {
        //回転する
        auto rotate = this->getItemRotate() + 20;
        this->setItemRotate(rotate);
        _elapseRotate = 0.0f; //戻す
    }
}

// 対角線の長さを取得
float DropItem::getDiagonal(DropItem* dropItem)
{
    // 長辺の2乗　＋　短辺の2乗　＝　対角線の2乗
    float d = powf(dropItem->getContentSize().width, 2) + powf(dropItem->getContentSize().height, 2);
    
    // 平方根
    float diagonal = sqrtf(d);
    
    return diagonal;
}