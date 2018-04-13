/**
 * Created by changhao on 4/12/2018.
 * Brief   :	地面
 */

cc.Class({
	extends: cc.Component,

	properties: {

	},

	// use this for initialization
	onLoad: function () {
		this.limitClick = this.node.getComponent("LimitClick");
	},

	setParent:function(_parent){

	},

	onCliclook:function (_bool) {
		if(_bool == true){
			this.setTipPos();
		}else{
			this.parentJS.onHideTip();
		}
	}
});
