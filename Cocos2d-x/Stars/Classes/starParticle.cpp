//
//  starParticle.cpp
//  Stars
//
//  Created by HAO on 16-2-18.
//
//

#include "Stars.h"
#include "starParticle.h"



void showStarParticleEffect(int color, Point position, Node* node){
    
//    ParticleExplosion* effect = ParticleExplosion::create();
//    effect->setTexture(Director::getInstance()->getTextureCache()->addImage("star.png"));
//	effect->setTotalParticles(15);
//	effect->setStartColor(getColor(color));
//	effect->setStartColorVar(Color4F(0,0,0,1));
//	effect->setEndColor(getColor(color));
//	effect->setEndColorVar(Color4F(0,0,0,1));
//	effect->setStartSize(25.0f);
//	effect->setGravity(Point(0,-300));
//	effect->setLife(5.0f);
//	effect->setSpeed(200);
//	effect->setSpeedVar(10);
//	effect->setPosition(position);
//    
//    
//	node->addChild(effect);
    
    
    ParticleExplosion* effect = ParticleExplosion::create();
    
    effect->cocos2d::ParticleSystem::setTexture(Director::getInstance()->getTextureCache()->addImage("star.png"));
    effect->cocos2d::ParticleSystem::setTotalParticles(15);
    
    effect->setStartColor(getColor(color));
    effect->setStartColorVar(Color4F(0, 0, 0, 1));
    
    effect->setEndColor(getColor(color));
    effect->setEndColorVar(Color4F(0, 0, 0, 1));
    
    effect->setStartSize(25.0f);
    
    effect->setGravity(Vec2(0, -300));
    
    effect->setLife(1.0f);
    
    effect->setSpeed(200);
    effect->setSpeedVar(10);
    
    effect->setPosition(position);
    
    node->addChild(effect);
    
}

Color4F getColor(int color){
    
    log("getColor!");
    
    switch(color){
            
        case Stars::color::PURPLE:
            return Color4F(0.74,0.30,0.99,1);
            
        case Stars::color::BLUE:
            return Color4F(84/255.0f,203/255.0f,254/255.0f,1);
            
        case Stars::color::RED:
            return Color4F(253/255.0f,80/255.0f,126/255.0f,1);
            
        case Stars::color::YELLOW:
            return Color4F(253/255.0f,234/255.0f,84/255.0f,1);
            
        case Stars::color::GREEN:
            return Color4F(132/255.0f,226/255.0f,111/255.0f,1);
            
	}
	return Color4F(1,1,1,0);
    
    
    log("getColor!");
}




