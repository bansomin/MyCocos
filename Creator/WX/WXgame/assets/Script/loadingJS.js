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
			percent = percent<0 ? 0 : percent;
			percent = percent>1 ? 1 : percent;
			cc.log(item.content._name + " -- " + percent);
			self.progressBar.progress = percent;
			self.label.string = "加载" + item.content._name + "中 " + percent * 100 + "%";
		};

		cc.director.preloadScene('startScene', function (error) {
				setTimeout(()=>{
					cc.director.loadScene('startScene');
				}, 3000);
			}
		);
	}
});
