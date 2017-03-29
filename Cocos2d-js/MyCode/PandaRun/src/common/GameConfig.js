/**
 * Created by HAO on 2017/2/2.
 * Brief   : 游戏配置
 * Version :
 */

var GC = GC||{};

GC.KEY = {
	USERNAME 		: 	"username",	//用户的名称KEY
	MUSIC_SILENCE	:	"ismusic",
	EFFECT_SILENCE	:	"iseffect",
	LEVLE			:	"level",		//用户选择的难易程度
	TOTALCOIN		:	"totalcoin",
	COIN			:	"coin",
	MAGNETNUM		:	"magnetnum",
	BLUESHOESNUM	:	"blueshoes",
	REDSHOESNUM 	:	"redshoes"
};

//游戏物品默认数量
GC.NUMBERS = {
	COIN		:	0,
	MAGNET		:	1,
	BLUESHOES	:	2,
	REDSHOES	:	3,
	GOLD		:	22,	//创建的金币数量
};


//物品价格
GC.PRICE = {
	MAGNET		:	30,
	BLUESHOES	:	50,
	REDSHOES	:	50
};

//价格标签类型
GC.ITEMS = {
	MAGNET		:	"magnet",
	BLUESHOES	:	"blueshoes",
	REDSHOES	:	"redshoes",
	GOLD		:	"gold",
	DOUBLEJUMP	:	"double-jump-shoes",
	SPEEDUP		:	"speed-up-shoes"
};

GC.LEVEL = false;
GC.MUSIC_SILENCE = true;
GC.EFFECT_SILENCE = true;

//金币
GC.NUMBERS.COIN = cc.sys.localStorage.getItem(GC.KEY.COIN);
if (GC.NUMBERS.COIN==null || GC.NUMBERS.COIN=="") {
	GC.NUMBERS.COIN = 110;
}

//磁铁
GC.NUMBERS.MAGNET = cc.sys.localStorage.getItem(GC.KEY.MAGNETNUM);
if (GC.NUMBERS.MAGNET==null || GC.NUMBERS.MAGNET=="") {
	GC.NUMBERS.MAGNET = 0;
}

//蓝鞋
GC.NUMBERS.BLUESHOES = cc.sys.localStorage.getItem(GC.KEY.BLUESHOESNUM);
if (GC.NUMBERS.BLUESHOES==null || GC.NUMBERS.BLUESHOES=="") {
	GC.NUMBERS.BLUESHOES = 0;
}

//红鞋
GC.NUMBERS.REDSHOES = cc.sys.localStorage.getItem(GC.KEY.REDSHOESNUM);
if (GC.NUMBERS.REDSHOES==null || GC.NUMBERS.REDSHOES=="") {
	GC.NUMBERS.REDSHOES = 0;
}

cc.log("金币" + GC.NUMBERS.COIN + "G 磁铁" + GC.NUMBERS.MAGNET + "个 蓝鞋" + GC.NUMBERS.BLUESHOES + "双 红鞋" + GC.NUMBERS.REDSHOES + "双");

GC.HIGH		= 80;
GC.HEROSPEEDUP = 1000;

GC.INFO = {
	NICKNAMERIGHT	:	"昵称已保存",
	NICKNAMEDEF		:	"使用默认昵称",
	NICKNAMEERROR	:	"昵称有误",
	BUYMAGNET		:	"购买磁铁成功",
	BUYBLUESHOES	:	"购买蓝鞋成功",
	BUYREDSHOES		:	"购买红鞋成功",
	BUYFAIL			:	"您的金币不足...",
	COINFULL		:	"您的小金库已经满喽..."
};

GC.SpriteTag = {
	player 		: 0,
	gold 		: 1,
	inventory	: 2,
	platform	: 3,
	ground		: 4,
	magnet		: 5,
	spring		: 6,
	shoes		: 7,
	redshoes	: 8,
	bird		: 9
};

GC.ROLESTATE = {
	RUN			:	"running",
	JUMPUP		:	"jumpUp",
	JUMPDOWN	:	"jumpDown"
};

GC.physics = {
	groundHeight: 0
};

//判断用户名是否合法
GC.CheckUserName = function (str) { //用户名必须是字母、数字、或中文
	var ret = new RegExp("^([\u4E00-\uFA29]|[\uE7C7-\uE7F3]|[a-zA-Z0-9])");
	if (ret.test(str)) {
		return true;
	}
	return false;
};


//备注
/*
*	GameBackgroundLayer	:	-1
*	Platform			:	1
*	Gold				:	5
*	Items				:	10
*	Hero				:	15
* */
