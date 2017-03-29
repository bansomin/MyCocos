/**
 * Created by HAO on 2017/2/2.
 * Brief   :	管理游戏的音效与声音
 * Version :
 */

var Sound = {

	_eatGoldEffect	:	0,

	playBGM : function () {
		cc.audioEngine.playMusic(res.sound.bgm1, true);
		if (GC.MUSIC_SILENCE) {
			cc.audioEngine.setMusicVolume(0.1);
		}
		else {
			cc.audioEngine.setMusicVolume(0);
		}
	},

	playEffectOpening : function () {
		if (GC.EFFECT_SILENCE) {
			cc.audioEngine.playEffect(res.sound.opening);
		}
	},

	playEffectBtn : function () {
		if (GC.EFFECT_SILENCE) {
			cc.audioEngine.playEffect(res.sound.button);
		}
	},

	playEffectJump : function () {
		if (GC.EFFECT_SILENCE) {
			cc.audioEngine.playEffect(res.sound.jump_mp3);
		}
	},

	playEffectEatGold : function () {
		if (GC.EFFECT_SILENCE) {
			//先停止之前播放的吃音效，否则会因为连续播放过多而报错
			if (Sound._eatGoldEffect) {
				cc.audioEngine.stopEffect(Sound._eatGoldEffect);
			}
			Sound._eatGoldEffect = cc.audioEngine.playEffect(res.sound.gold_mp3, false);
		}
	},

	toggleEffectOnOff : function () {
		cc.log("toggleEffectOnOff");

		if (GC.EFFECT_SILENCE) {
			GC.EFFECT_SILENCE = false;
			cc.audioEngine.setEffectsVolume(0);
		}
		else {
			GC.EFFECT_SILENCE = true;
			cc.audioEngine.setEffectsVolume(1);
		}

		//保存到本地
		cc.sys.localStorage.setItem(GC.KEY.EFFECT_SILENCE, GC.EFFECT_SILENCE);
	},

	toggleMusicOnOff : function () {
		cc.log("toggleMusicOnOff");

		if (GC.MUSIC_SILENCE) {
			GC.MUSIC_SILENCE = false;
			cc.audioEngine.setMusicVolume(0);
		}
		else {
			GC.MUSIC_SILENCE = true;
			cc.audioEngine.setMusicVolume(0.1);
		}

		//保存到本地
		cc.sys.localStorage.setItem(GC.KEY.MUSIC_SILENCE, GC.MUSIC_SILENCE);
	}

};