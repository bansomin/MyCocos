/**
 * Created by HAO on 2016/11/25.
 * Brief   :	关卡信息界面
 * Version :
 */

var LevelInforModel = cc.Sprite.extend({

	_levelBg		:	null,	//关卡背景图
	_levelValue		:	1,		//当前关卡数
	_levelTotalValue:	10,		//总关卡数
	_levelLabel		:	null,	//关卡标签

	_timeBg			:	null,	//时钟背景图
	_timeValue		:	0,		//时间
	_timeLabel		:	null,	//时间标签

	ctor : function (time) {
		
		this._super();

		Wsize = cc.director.getWinSize();
		this._timeValue = time;

		this.init();
		
		return true;
	},
	
	init : function () {

		//关卡背景
		this._levelBg = new cc.Sprite("#guanqia.png");
		this._levelBg.setPositionY(200);
		this.addChild(this._levelBg);

		//时间背景
		this._timeBg = new cc.Sprite("#time.png");
		//this._timeBg.setPosition(this._timeBg.getContentSize().width*1.3, -60);
		this._timeBg.setPosition(Wsize.width + this._timeBg.getContentSize().width, -60);
		this.addChild(this._timeBg);

		//时间标签
		this._timeLabel = new cc.LabelBMFont(this.changeTimeFormat(this._timeValue), res.font_fnt_lvl);
		this._timeLabel.setScale(0.7);
		this._timeLabel.setPosition(this._levelBg.getContentSize().width/2 + 20,
										this._levelBg.getContentSize().height/4 - 5);
		this._timeBg.addChild(this._timeLabel);

		this.actionFunc("in");
		this.addLevel();
	},

	addLevel : function (level, totalLevel) {

		if (level!=null && totalLevel!=null) {
			this._levelValue = level;
			this._levelTotalValue = totalLevel;
		}
		//关卡标签
		var text = this._levelValue + "/" + this._levelTotalValue;
		this._levelLabel = new cc.LabelBMFont(text, res.font_fnt_lvl);
		this._levelLabel.setPosition(this._levelBg.getContentSize().width/2,
			this._levelBg.getContentSize().height/3);
		this._levelBg.addChild(this._levelLabel);

	},

	setLevel : function (level) {
		this._levelValue = level;
		this._levelLabel.setString(this._levelValue + "/" + this._levelTotalValue);
	},

	getLevel : function () {
		return this._levelValue;
	},

	//开始计时器
	startTimer : function () {
		//更新计时
		this.schedule(this.upateTimer, 1);
	},

	//停止计时器
	stopTimer : function () {
		this.unschedule(this.upateTimer);
	},

	upateTimer : function () {
		//cc.log("update");
		if (this._timeValue < 0) {
			return;
		}
		this._timeValue++;
		this.setTimer(this._timeValue);
	},

	//设置时间
	setTimer : function (time) {
		this._timeValue = time;
		this._timeLabel.setString(this.changeTimeFormat(this._timeValue));

		// if (this._timeValue <= 10) {
		// 	this.timerAction();
		// }
		this.timerAction();
	},

	getTimer : function () {
		return this._timeValue;
	},

	//显示器动画
	timerAction : function () {

		var scale = cc.scaleTo(0.1, 1.05, 1.05).easing(cc.easeBackInOut());
		//var reverse = scale.reverse();
		var reverse = cc.scaleTo(0.1, 1, 1).easing(cc.easeBackInOut());
		var seq = cc.sequence(scale, reverse);
		this._timeBg.runAction(seq);
	},

	//转换时间格式
	changeTimeFormat : function (time) {

		if (time > 3598) {
			this._timeValue = 0;
		}

		var mins = parseInt(time/60);
		var secs = time - mins*60;

		if (mins<10) {
			mins = "0" + mins;
		}

		if (secs<10) {
			secs = "0" + secs;
		}

		//cc.log("TIME ：" + mins + " : " + secs);

		return (mins + ":" + secs);
	},

	//关卡信息的动作
	actionFunc : function (type) {

		var lvlMoveToIn = cc.moveTo(1, 0, 0).easing(cc.easeBackInOut());
		var timeMoveToIn = cc.moveTo(1, this._timeBg.getContentSize().width*1.3, -60).easing(cc.easeBackInOut());

		//var re_lvlMoveToIn = lvlMoveToIn.reverse();
		var re_lvlMoveToIn = cc.moveTo(1, 0, 200).easing(cc.easeBackInOut());
		//var re_timeMoveToIn = timeMoveToIn.reverse();
		var re_timeMoveToIn = cc.moveTo(1, this._levelBg.getContentSize().width/2 + 20, this._levelBg.getContentSize().height/4 - 5).easing(cc.easeBackInOut());

		switch (type){
			case "in" :
				this._levelBg.runAction(lvlMoveToIn);
				this._timeBg.runAction(timeMoveToIn);
				break;
			case "out":
				this._levelBg.runAction(re_lvlMoveToIn);
				this._timeBg.runAction(re_timeMoveToIn);
				break;
		}
	}

});