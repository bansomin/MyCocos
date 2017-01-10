/**
 * Created by HAO on 2016/12/2.
 * Brief   : 游戏音效管理
 * Version :
 */

/*
* 背景音乐、音效的播放、静音
* */
var SoundManager = {

	//敲打音效
	playHitSound : function (volume) {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_hit);
		}
	},

	//按钮音效
	playBtnSound : function (volume) {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_btn);
		}
	},

	//正确音效
	playRightSound : function (volume) {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_right);
		}
	},

	//错误音效
	playWrongSound : function (volume) {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_wrong);
		}
	},

	//选择字母音效
	playSelectSound : function (volume) {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_select);
		}
	},

	//倒计时音效
	playCountDownSound : function (volume) {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_countDown);
		}
	}

};