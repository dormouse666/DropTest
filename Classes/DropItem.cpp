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
    }
}

// 動かせるか判定
bool DropItem::canPlace(DropItem* dropItem, cocos2d::Node* backGround)
{
    //親の座標に変換
    auto itemPos = backGround->convertToWorldSpace(dropItem->getPosition());

    auto minX = backGround->getPositionX() - backGround->getContentSize().width/2;
    auto maxX = backGround->getPositionX() + backGround->getContentSize().width/2;
    auto minY = backGround->getPositionY() - backGround->getContentSize().height/2;
    //auto maxY = backGround->getPositionY() + backGround->getContentSize().height/2;
    
    if(itemPos.x < minX || itemPos.x >= maxX || itemPos.y < minY)
    {
        return false;
    }
    
    return true;
}
