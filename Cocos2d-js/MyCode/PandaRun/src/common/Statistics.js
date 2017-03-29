/**
 * Created by HAO on 2017/2/17.
 * Brief   :
 * Version :
 */

var Statistics = {

	coins 	:	0,
	meter	:	0,
	kill	:	0,
	hero	:	null,

	get scoreFunc(){
		return this.coins * 10;
	},

	get length(){
		return parseInt(this.hero._sprite.getPositionX()/100);
	},

	reset : function (hero) {
		this.hero = hero;
		this.coins = 0;
		this.meter = 0;
		this.kill = 0;
	}
};