/**
 * Created by HAO on 2016/12/12.
 * Brief   :
 * Version :
 */

var LevelInforModel = cc.Sprite.extend({

	_levelValue		:	1,		//当前关卡数
	_levelTotalValue:	10,		//总关卡数
	_levelLabel		:	null,	//关卡标签

	_timeBg			:	null,	//时钟背景图
	_timeValue		:	0,		//时间
	_timeLabel		:	null,	//时间标签

	_levelSpr		:	null,


	ctor : function (time, level, totalLevel) {

		this._super();

		Wsize = cc.director.getVisibleSize();

		if (time) {
			this._timeValue = time;
		}
		if (level) {
			this._levelValue = level;
		}
		if (totalLevel) {
			this._levelTotalValue = totalLevel;
		}


		this.init();

		return true;
	},

	init : function () {

		//关卡标签
		var text = this._levelValue + "/" + this._levelTotalValue;
		this._levelLabel = new cc.LabelBMFont(text, res.font_fnt_lvl);
		this._levelLabel.setPosition(0, Wsize.height + this._levelLabel.getContentSize().height);
		this.addChild(this._levelLabel);

		this._levelLabel.runAction(
			cc.moveTo(
				1, 0, -Wsize.height/14
			).easing(cc.easeBackInOut())
		);

		//时间背景
		this._timeBg = new cc.Sprite("#time.png");
		this._timeBg.setPosition(Wsize.width + this._timeBg.getContentSize().width,
								-Wsize.height/14 - this._timeBg.getContentSize().height - this._levelLabel.getContentSize().height);
		this.addChild(this._timeBg);
		var timeMoveToIn = cc.moveTo(1,
									this._timeBg.getContentSize().width,
									-Wsize.height/14 - this._timeBg.getContentSize().height - this._levelLabel.getContentSize().height
									).easing(cc.easeBackInOut());
		this._timeBg.runAction(timeMoveToIn);

		//时间标签
		this._timeLabel = new cc.LabelBMFont(this.changeTimeFormat(this._timeValue), res.font_fnt_lvl);
		this._timeLabel.setScale(0.6);
		this._timeLabel.setPosition(this._timeBg.getContentSize().width*2/3, this._timeBg.getContentSize().height/2 - 5);
		this._timeBg.addChild(this._timeLabel);

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
	}

});