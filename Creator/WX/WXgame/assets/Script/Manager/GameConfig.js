/**
 * Created by changhao on 4/13/2018.
 * Brief   :
 */

var GC = GC || {};

GC.NO         = 1;
GC.CUR_SCORE  = 0;
GC.CUR_USER   = null;

//棍子增加的速度
GC.scaleSpeed = 0.01;

//屏幕的移动速度
GC.screenTime = 0.5;

//新黑块左移动速度
GC.newBlackTime = 1.5;

GC.scaleData = [0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3 , 0.2, 0.1];

var HERO_ANIMA_NAME = cc.Enum({
	kick	:	"Hero_kick",
	shake	:	"Hero_shake",
	walk	:	"Hero_walk",
	yao		:	"Hero_yao"
});

module.exports = {
	HERO_ANIMA_NAME	:	HERO_ANIMA_NAME,
	GC:GC
};





