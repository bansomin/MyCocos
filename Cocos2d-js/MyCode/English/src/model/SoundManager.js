/**
 * Created by HAO on 2016/12/2.
 * Brief   : 游戏音效管理
 * Version :
 */

/*
 * 背景音乐、音效的播放、静音
 * */
var SoundManager = {

	//播放背景音乐
	playBGMSound : function () {
		if (RCCommon.IsMusicOn) {
			cc.audioEngine.playMusic(res.music_bgm, true);
		}
	},

	//按钮音效
	playBtnSound : function () {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_btn, false);
		}
	},

	//正确音效
	playRightSound : function () {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_right, false);
		}
	},

	//错误音效
	playWrongSound : function () {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_wrong, false);
		}
	},

	//选择字母音效
	playSelectSound : function () {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_select, false);
		}
	},

	//敲打音效
	playHitSound : function () {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_hit, false);
		}
	},

	//倒计时音效
	playCountDownSound : function () {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_countDown, false);
		}
	},

	//ReadyGo
	playReadyGoSound : function () {
		if (RCCommon.IsEffectOn) {
			cc.audioEngine.playEffect(res.music_readygo, false);
		}
	},

	toggleOnOff : function () {
		cc.log("SoundManage_toggleOnOff");

		if (RCCommon.IsMusicOn) {
			RCCommon.IsMusicOn = false;
			cc.audioEngine.pauseMusic();
		}
		else {
			RCCommon.IsMusicOn = true;
			cc.audioEngine.resumeMusic();
		}
	}

};