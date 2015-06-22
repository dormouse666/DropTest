//
//  DropItem.h
//  dormouseTest
//
//  Created by dormouse666 on 2015/06/21.
//
//

#ifndef __dormouseTest__DropItem__
#define __dormouseTest__DropItem__

class DropItem : public cocos2d::Node
{
public:
    enum ColorType {
        BLUE,
        RED,
        BLACK,
        GREEN,
        ORANGE,
        PURPLE,
        YELLOW,
    };
    
public:
    DropItem();
    ~DropItem();
    
    void onEnter() override;
    void onExit() override;
    
    virtual bool init();
    CREATE_FUNC(DropItem);
    
    ColorType randomItemColor();
    void setItemType(ColorType type);
    
    bool canPlace(DropItem* _dropItem, cocos2d::Node* _backGround);

private:
    cocos2d::Sprite* _spr;
    
};

#endif /* defined(__dormouseTest__DropItem__) */
