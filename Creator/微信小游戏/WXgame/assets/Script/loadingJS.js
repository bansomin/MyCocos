/**
 * Created by changhao on 4/12/2018.
 * Brief   :	加载界面
 */

cc.Class({
	extends: cc.Component,

	properties: {

		label		:	cc.Label,		//提示
		progressBar	:	cc.ProgressBar	//进度条
	},

	// use this for initialization
	onLoad: function () {

		this.loading();
	},

	loading: function () {
		cc.log("loading");

		var self = this;
		cc.loader.onProgress = function (completedCount, totalCount, item) {
			var percent = Math.floor(completedCount/totalCount).toFixed(2);
			cc.log("percent : " + percent);

		/*	percent = percent<0 ? 0 : percent;
			percent = percent>1 ? 1 : percent;
			self.progressBar.fillRange = percent;
			self.label.node.setPositionX(self.progressBar.node.width * percent * 100%);
			self.label.string = percent + "%";*/
		}
	}
});
