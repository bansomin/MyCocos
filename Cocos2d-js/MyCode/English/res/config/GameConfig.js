
/**
 * Created by HAO on 2016/11/24.
 * Brief   :	全局项
 * Version :
 */

var GC = GC || {};

GC.ANIMATIONTYPE = {
	COUNTDOWN	:	"countdown",
	HAMMER		:	"hammer",
	OUT			:	"out",
	IN			:	"in",
	SHOW		:	"show",
	HIDE		:	"hide",
	SOUND		:	"sound"
};

GC.WORDNUMBERSOFLVL = 10;	//每一关单词数目

GC.NUMBEROFHAMSTER = 16;

//间隔
GC.DISBWTLETTER 	= 180;		//调节显示单词间隔
GC.DISBWTHAMSTER 	= 25;		//地鼠间隔
GC.DISBWTWORD		= 10;		//单词间隔

//速度
GC.LETTER_SPEED = 400;

GC.LETTER_TAG = 500;		//第一个字母的TAG值
GC.LACKLETTER_TAG = 200;		//第一个字母的TAG值

GC.BOXWIDTH  = 150;
GC.BOXHEIGHT = 150;

GC.LETTERARRAY = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'];

GC.randomNeedLetterArray = function (word) {

	var len = word.length;
	if (len<=0) {
		return;
	}

	var array = [];
	var returnArray = [];
	var numberMax = parseInt(len/2);

	var number = parseInt(numberMax*Math.random() + 1);	// 1----numberMax

	cc.log("单词长度为 " + len + " 最多可以隐藏 " + numberMax + " 需要隐藏 " + number);

	for(var i = 0; i<len; i++){
		array[i] = i;
	}

	for(var i = 0;i<len;i++){
		var rand = parseInt(len * Math.random());
		var temp = array[i];
		array[i] = array[rand];
		array[rand] = temp;
	}

	//取前number位
	for (var i = 0; i < number; i++) {
		returnArray.push(array[i]);
		cc.log("array : " + array[i]);
	}

	return GC.sortArray(returnArray);
};

//冒泡法排序
GC.sortArray = function (array) {

	var len = array.length;
	if (len <= 0) {
		return;
	}

	for (var i = 0; i < len-1; i++) {
		for (var j = i+1; j < len; j++) {
			if (array[i] > array[j]) {
				var temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}

	return array;
};

//打乱16个数组顺序
GC.randomMyArray = function () {
	cc.log("GameConfig_RandomMyArray.");

	var array = [];
	for(var i = 0; i<GC.NUMBEROFHAMSTER; i++){
		array[i] = i;
	}

	for(var i = 0;i<GC.NUMBEROFHAMSTER;i++){
		var rand = parseInt(GC.NUMBEROFHAMSTER * Math.random());
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
		case "out" :	//地鼠出洞
			for (var i = 4; i >0 ; i--) {
				var frameName = "dishu0" + i + ".png";
				//cc.log("frameName : " + frameName);
				animation.addSpriteFrame(cc.spriteFrameCache.getSpriteFrame(frameName));
			}
			animation.setDelayPerUnit(1/20);
			break;

		case "in" :		//地鼠进洞
			for (var i = 1; i < 5; i++) {
				var frameName = "dishu0" + i + ".png";
				//cc.log("frameName : " + frameName);
				animation.addSpriteFrame(cc.spriteFrameCache.getSpriteFrame(frameName));
			}
			animation.setDelayPerUnit(1/20);
			break;

		case "hammer" :	//锤子动画
			for (var i = 1; i < 5; i++) {
				var frameName = "0" + i + ".png";
				animation.addSpriteFrame(cc.spriteFrameCache.getSpriteFrame(frameName));
			}
			animation.setDelayPerUnit(1/20);
			break;

		case "countdown" :	//倒计时动画
			for (var i = 3; i > 0; i--) {
				var frameName = i + ".png";
				animation.addSpriteFrame(cc.spriteFrameCache.getSpriteFrame(frameName));
			}
			animation.setDelayPerUnit(1);
			break;

		case "sound" :	//音乐图标动画
			for (var i = 0; i < 3; i++) {
				var frameName = "soundOn000" + i + ".png";
				//cc.log("frameName : " + frameName);
				animation.addSpriteFrame(cc.spriteFrameCache.getSpriteFrame(frameName));
			}
			animation.setDelayPerUnit(1/3);
			break;

	}

	animation.setRestoreOriginalFrame(false);

	return cc.animate(animation);
};
