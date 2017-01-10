/**
 * Created by HAO on 2016/12/9.
 * Brief   :
 * Version :
 */

var GC = GC || {};

GC.LVL_TOTALNUMBERS = 10;		//总共关卡数
GC.IDIOM_CANDIDATENUMBERS = 4;	//候选成语个数

GC.DIS_BETEDGE  = 10;
GC.DIS_BETWORD 	= 25;			//汉字间隔

GC.DIS_BETANSWERWORD = 110;

GC.TAG_UNDEFINE	= 999;			//未定义TAG值
GC.TAG_ANSWERWORD = 100;		//答案汉字的基本TAG

GC.ACTIONTYPE = {
	TOMID	:	"tomid",
	TOTOP	:	"totop"
};

GC.ANIMATIONTYPE = {
	COUNTDOWN	:	"countdown",
	CLICK		:	"click",
	LIGHT		:	"light"
};

//打乱指定个数数组顺序
GC.reshuffleArray = function (len) {
	cc.log("GameConfig_RandomMyArray.");

	if (len<=0) {
		return;
	}

	var array = [];
	for(var i = 0; i<len; i++){
		array[i] = i;
	}

	for(var i = 0;i<len;i++){
		var rand = parseInt(len * Math.random());
		var temp = array[i];
		array[i] = array[rand];
		array[rand] = temp;
	}

	return array;
};

/**
 * 动画
 */
GC.prepareAnimation = function (type) {
	cc.log("type : " + type);

	var animation = new cc.Animation();

	switch (type){
		case "click" :		//地鼠进洞
			for (var i = 1; i < 4; i++) {
				var frameName = "GK_guangquan_" + i + ".png";
				//cc.log("frameName : " + frameName);
				animation.addSpriteFrame(cc.spriteFrameCache.getSpriteFrame(frameName));
			}
			animation.setDelayPerUnit(1/10);
			break;

		case "light" :	//倒计时动画
			for (var i = 1; i < 16; i++) {
				var frameName = "";
				if (i<10) {
					frameName = "guang_0" + i + ".png";
				}
				else {
					frameName = "guang_" + i + ".png";
				}
				animation.addSpriteFrame(cc.spriteFrameCache.getSpriteFrame(frameName));
			}
			animation.setDelayPerUnit(1/10);
			break;

		case "countdown" :	//倒计时动画
			for (var i = 3; i > 0; i--) {
				var frameName = i + ".png";
				animation.addSpriteFrame(cc.spriteFrameCache.getSpriteFrame(frameName));
			}
			animation.setDelayPerUnit(1);
			break;
	}

	animation.setRestoreOriginalFrame(false);

	return cc.animate(animation);
};
