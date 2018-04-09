/**
 * Created by Bansomin on 4/9/2018.
 * Brief   :	验证窗口
 */

/*
* 0-失败
* 1-通过
* 2-开始
* */
var VALIDATE_TYPE = cc.Enum({
	FAIL		:	0,
	SUCCESS     :	1,
	BEGIN       :	2
});
const totalTime = 10000;
cc.Class({
	extends: cc.Component,

	properties: {

		titleSpr	:	cc.Sprite,			//标题
		titleSFList : 	[cc.SpriteFrame],

		maskNode	:	cc.Node,			//mask
		line		:	cc.Node,			//扫描线

		succSpr		:	cc.Node,			//扫描结果
		failSpr		:	cc.Node,

		timeLabel	:	cc.Label,	//时间
		progressBar	:	cc.ProgressBar,

		btnsNode	:	cc.Node,
		closeBtnNode:	cc.Node,
		_isScan  	:	true,
		_curTimer	:	0
	},

	// use this for initialization
	onLoad: function () {

		this.maskH = this.maskNode.getContentSize().height;
		this.lineH = this.line.getContentSize().height;
		cc.log(this.maskH + " ***** " + this.lineH);
		this.line.setPositionY(this.maskH/2);
	},

	onEnable: function () {
		this.initData();
	},

	initData: function () {
		this._curTimer = Date.now();;
		this._countDownTimer = totalTime + Date.now();
		this.setResultData(VALIDATE_TYPE.BEGIN);

		//初始化时间
		this.updateTime(totalTime);
	},

	setResultData: function (type) {
		this.titleSpr.spriteFrame = this.titleSFList[type];	//设置标题
		this.closeBtnNode.active = type==VALIDATE_TYPE.BEGIN;
		this.succSpr.active = type==VALIDATE_TYPE.SUCCESS;
		this.btnsNode.active = type==VALIDATE_TYPE.FAIL;
		this.failSpr.active = type==VALIDATE_TYPE.FAIL;
	},

	update: function () {

		if(this._isScan){
			if(this.line.getPositionY() < -(this.maskH/2 + this.lineH)){
				this.line.setPositionY(this.maskH/2);
			}else {
				var pos = this.line.getPositionY() - 5;
				this.line.setPositionY(pos);
			}
		}

		this._diff = this._countDownTimer-Date.now();
		this._diff = (this._diff>=0 && this._diff<=25) ? 0 : this._diff;
		if(this._diff >= 0){
			if(this._diff == 0) this.setResultData(VALIDATE_TYPE.FAIL);
			this.updateProgressBar();
		}
		if(Date.now()-this._curTimer>=1000 && this._diff>=-100){
			this._curTimer = Date.now();
			this.updateTime();
		}
	},

	updateTime:function (_time) {
		var time = (_time==null) ? this._diff : _time;
		var num = Math.round(time/1000);
		if(this.timeLabel) this.timeLabel.string = "剩余时间:" + num + "S";
	},

	updateProgressBar: function () {
		if(this.progressBar){
			var rate = 1- (this._diff / totalTime);
			this.progressBar.progress = rate;
		}
	},

	//重新验证
	onClickReBtn: function (evn, type) {
		this.initData();
	},

	onClickClose: function(evn, type){
		this.node.active = false;
	}
});
