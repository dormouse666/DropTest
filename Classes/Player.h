//
//  Player.h
//  dormouseTest
//
//  Created by dormouse666 on 2015/06/30.
//
//

#ifndef __dormouseTest__Player__
#define __dormouseTest__Player__

class Player : public cocos2d::Node
{
public:
    Player();
    ~Player();
    
    void onEnter() override;
    void onExit() override;
    
    virtual bool init();
    CREATE_FUNC(Player);
    
private:
    cocos2d::Sprite* _spr;
};

#endif /* defined(__dormouseTest__Player__) */
