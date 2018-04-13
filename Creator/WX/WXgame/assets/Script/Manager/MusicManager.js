/**
 * Created by changhao on 4/13/2018.
 * Brief   :	声音管理
 */

var MusicManager = cc.Class({

	playBGM: function () {

		var audioUrl = this.getUrl("bg");
		this.stopBGM();
		if(Global.musicFlag==true){
			Global.musicSound = cc.audioEngine.play(audioUrl, true)
		}
	},

	stopBGM: function () {

		if(Global.musicSound != null){
			Global.musicSound.stop();
			Global.musicSound = null;
		}
	},

	playClickSound: function () {

		this.playSound("dianji");
	},

	playSound: function (_url) {
		var audioUrl = this.getUrl(_url);
		cc.audioEngine.play(audioUrl, false);
	},

	getUrl: function (url) {
		return cc.url.raw("resources/sound/" + url + ".mp3");
	}
});