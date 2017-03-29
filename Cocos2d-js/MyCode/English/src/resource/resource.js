var res = {

    /********************************************************/
    //游戏合图
    plist_dancisupin:   "res/plist/dancisuping_yasu.plist",
    png_dancisupin  :   "res/plist/dancisuping_yasu.png",
	//声音
	plist_two:   "res/plist/soundplist.plist",
    png_two  :   "res/plist/soundplist.png",

    //游戏字体
    font_fnt_aht    :   "res/font/aht.fnt",
    font_png_aht    :   "res/font/aht.png",
    font_fnt        :   "res/font/comic2.fnt",
    font_png        :   "res/font/comic2.png",
    font_fnt_p      :   "res/font/comic.fnt",
    font_png_p      :   "res/font/comic.png",
    font_fnt_lvl    :   "res/font/rockwell.fnt",
    font_png_lvl    :   "res/font/rockwell.png",
    font_fnt_cnt    :   "res/font/xinwei.fnt",    //剩余次数
    font_png_cnt    :   "res/font/xinwei.png",

    //背景
    png_bg_start    :   "res/pic/bg.png",
    //png_bg_game     :   "res/pic/bg02.png",
    png_bg_game     :   "res/pic/bg02.jpg",
    png_bg_rule     :   "res/pic/yxgz.png",
    png_bg_action   :   "res/pic/bg003.png",
    png_bg_result   :   "res/pic/tanchuang.png",

    //退出图片
    png_exit        :   "res/pic/exit.png",

	music_bgm       :   "res/music/bgm.mp3",
	music_hit       :   "res/music/hit.mp3",
	music_btn       :   "res/music/btn4.mp3",
	music_wrong     :   "res/music/wrong1.mp3",
	music_right     :   "res/music/right.mp3",
	music_select    :   "res/music/btn3.mp3",
	music_readygo	:   "res/music/readygo.mp3",
	music_countDown :   "res/music/down1.mp3"

};

var g_resources = [];
for (var i in res) {
    g_resources.push(res[i]);
}
