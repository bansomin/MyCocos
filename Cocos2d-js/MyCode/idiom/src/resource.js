var res = {

    //合图
    graph_plist :   "res/pic/graph.plist",
    graph_png   :   "res/pic/graph.png",
	
	    //退出图片
    png_exit        :   "res/pic/exit.png",

    //图片
	png_applogo		:	"res/pic/applogo.png",
	png_startBg		:	"res/pic/start_bg.png",
    png_gameBg      :   "res/pic/gm_bg.png",
	png_answer      :   "res/pic/dikuang.png",
	png_bg_rule     :   "res/pic/yxgz.png",
	png_bg_action   :   "res/pic/bg003.png",
	png_bg_result   :   "res/pic/tanchuang.png",
	png_bg_exp   	:   "res/pic/bgExp.png",
	png_bg_from  	:   "res/pic/juanzhoudi.png",

	//错误
	png_wrongbg		:	"res/pic/wrongbg.png",
	png_replay		:	"res/pic/replay.png",
	png_replay_pre	:	"res/pic/replay_press.png",

    //json
    json_idiom_01   :   "res/json/idiom_01.json",

    //字体
	font_fnt_lvl    :   "res/font/rockwell.fnt",
	font_png_lvl    :   "res/font/rockwell.png",

	// "fonts" : {
	// 	type : "font",
	// 	name : "arial",
	// 	srcs : ["res/font/arial.ttf"]
	// }

};

var g_resources = [
];
for (var i in res) {
    g_resources.push(res[i]);
}
