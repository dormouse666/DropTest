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
    constexpr static const float ROTATE_INTERVAL_DEFAULT = 0.2f;
    
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
    
    bool canPlace(cocos2d::Node* _backGround);
    
    void setItemRotate(int rotate);
    int getItemRotate();
    
    void update(float dt);
    
    float getDiagonal();

private:
    cocos2d::Sprite* _spr;
    
    int _itemRotate;
    float _elapseRotate;
    float _rotateInterval;
};

#endif /* defined(__dormouseTest__DropItem__) */
