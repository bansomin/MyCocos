/**
 * Created by HAO on 2017/2/4.
 * Brief   : 切换按钮封装
 * Version :
 */

var SoundToggleCell = cc.MenuItemToggle.extend({

	_isMusic	:	false,

	ctor : function (isMusic) {

		this._isMusic = isMusic;

		//从本地中读取当前音乐，音效状态并初始化
		if (isMusic) {	//音乐控制
			if (GC.MUSIC_SILENCE) {
				this._super(new cc.MenuItemImage("#on-btn.png"), new cc.MenuItemImage("#off-btn.png"));
			}
			else {
				this._super(new cc.MenuItemImage("#off-btn.png"), new cc.MenuItemImage("#on-btn.png"));
			}
		}
		else {	//音效控制
			if (GC.EFFECT_SILENCE) {
				this._super(new cc.MenuItemImage("#on-btn.png"), new cc.MenuItemImage("#off-btn.png"));
			}
			else {
				this._super(new cc.MenuItemImage("#off-btn.png"), new cc.MenuItemImage("#on-btn.png"));
			}
		}
		this.setCallback(this.switchStatusFunc, this);

	},

	switchStatusFunc : function () {

		Sound.playEffectBtn();

		//分别调用不同的声音控制函数
		if (this._isMusic) {
			Sound.toggleMusicOnOff();	//调用音乐控制函数
		}
		else {
			Sound.toggleEffectOnOff();	//调用音效控制函数
		}
	}

});

var LevelToggleCell = cc.MenuItemToggle.extend({

	ctor : function () {

		if (GC.LEVEL) {
			this._super(new cc.MenuItemImage("#high-btn.png"), new cc.MenuItemImage("#low-btn.png"));
		}
		else {
			this._super(new cc.MenuItemImage("#low-btn.png"), new cc.MenuItemImage("#high-btn.png"));
		}

		this.setCallback(this.switchStatusFunc, this);
	},

	switchStatusFunc : function () {
		cc.log("switch_Level");

		Sound.playEffectBtn();

		//保存难易程度到本地
		GC.LEVEL = !GC.LEVEL;
		cc.sys.localStorage.setItem(GC.KEY.LEVLE, GC.LEVEL);
		//cc.log("保存本地 ： " + cc.sys.localStorage.getItem(GC.KEY.LEVLE));
	}

});
