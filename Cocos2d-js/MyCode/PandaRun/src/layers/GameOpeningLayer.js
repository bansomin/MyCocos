/**
 * Created by HAO on 2017/2/2.
 * Brief   : 封装游戏初始logo界面及动画(资源预加载)
 * Version :
 */

var GameOpeningLayer = cc.Layer.extend({
	
	ctor : function () {
		this._super();

		Wsize = cc.director.getWinSize();

		//开始界面背景
		var bg = new cc.Sprite(res.open.bg);
		bg.setPosition(Wsize.width/2, Wsize.height/2);
		this.addChild(bg);

		//开始界面的logo
		var logo = new cc.Sprite(res.open.logo);
		logo.setPosition(Wsize.width/2, Wsize.height/2);
		logo.setScale(0.4);
		logo.opacity = 0;		//设置透明度
		this.addChild(logo);

		logo.runAction(
			seq = cc.sequence(
				cc.fadeIn(1.0),
				cc.delayTime(1.0),
				cc.fadeOut(1.0)
			)
		);

		//播放音效
		Sound.playEffectOpening();

		//预加载资源
		cc.spriteFrameCache.addSpriteFrames(res.graph.plist);		//图片合图
		cc.spriteFrameCache.addSpriteFrames(res.panda.plist);		//熊猫
		cc.spriteFrameCache.addSpriteFrames(res.gold.plist);		//金币
		cc.spriteFrameCache.addSpriteFrames(res.platform.plist);	//平台
		cc.spriteFrameCache.addSpriteFrames(res.shoes.plist);		//蓝色双跳鞋子
		cc.spriteFrameCache.addSpriteFrames(res.redshoes.plist);		//红色双跳鞋子
		cc.spriteFrameCache.addSpriteFrames(res.magnet.plist);

		// cc.spriteFrameCache.addSpriteFrames(res.bird.plist);
		// cc.spriteFrameCache.addSpriteFrames(res.enemy.plist);

		return true;
	}
	
});