var res = {

	"graph" : {
		plist	:	"res/pandaRun.plist",
		png		:	"res/pandaRun.png"
	},

	"mode" : {
		board	: 	"res/mode-board.png",
		mode1	: 	"res/mode1.png",
		mode2	: 	"res/mode2.png"
	},

	"bg" : {
		bg1	:	"res/far-bg.png",
		bg2 :	"res/near-bg.png"
	},

	"info" : {
		board	: 	"res/info-board.png",
		done	: 	"res/done.png"
	},

	"rank" : {
		board   : "res/rank-board.png"
	},

	//////////////////
	//menu
	"menu" : {
		bg			: 	"res/menu-bg.png",
		playBtn		: 	"res/play-btn.png",
		playBtnS	: 	"res/play-btn-s.png",
		storeBtn	: 	"res/rank-btn.png",
		storeBtnS	: 	"res/rank-btn.png",
		setBtn		: 	"res/set-btn.png",
		setBtnS		: 	"res/set-btn-s.png",
		startBtn	: 	"res/start-btn-normal.png",
		startBtnS	: 	"res/start-btn-selected.png",
		aboutBtn	: 	"res/about-btn.png",
		aboutBtnS	: 	"res/about-btn-s.png",
		logo		: 	"res/game-logo.png",
		wait		: 	"res/wait.png",
		enable		: 	"res/enable.png",
		disable		: 	"res/disable.png"
	},

	"ui" : {
		goldbar     : "res/ui/gold-bar.png",
		energybar   : "res/ui/energy-bar.png",
		progress    : "res/ui/progress.png",
		soundOn     : "res/ui/soundOnBtn.png",
		soundOff    : "res/ui/soundOffBtn.png",
		distance    : "res/ui/distance.png",
		aboutBoard  : "res/ui/about-board.png",
		backBtn     : "res/ui/back-btn.png",
		setBoard    : "res/ui/set-board.png",
		onBtn       : "res/ui/on-btn.png",
		offBtn      : "res/ui/off-btn.png",
		highBtn     : "res/ui/high-btn.png",
		lowBtn      : "res/ui/low-btn.png",
		storeBoard  : "res/ui/store-board.png",
		buy30       : "res/ui/buy-30.png",
		buy50       : "res/ui/buy-50.png",
		magnetProp  : "res/ui/magnet-prop.png",
		shoesProp   : "res/ui/shoes-prop.png",
		redshoesProp: "res/ui/redshoes-prop.png"
	},

	//********************进入动画界面图片********************
	"open" : {
		bg      : "res/open-bg.png",
		logo    : "res/maxon-team.png"
	},

	//********************声音********************
	"sound" : {
		bgm1		: "res/sound/bg.mp3",
		bgm2		: "res/sound/bg1.mp3",
		jump_mp3    : "res/sound/jump.mp3",
		gold_mp3    : "res/sound/eat.mp3",
		game_over   : "res/sound/game_over.mp3",
		button      : "res/sound/button.mp3",
		menu        : "res/sound/menu.mp3",
		opening     : "res/sound/opening.mp3",
		enemyDied   : "res/sound/enemyDied.mp3",
		magnet      : "res/sound/magnet.mp3",
		lose_prop   : "res/sound/lose_prop.mp3",
		spring      : "res/sound/spring.mp3",
		speedup     : "res/sound/speedup.mp3",
		alert       : "res/sound/alert.mp3",
		shopping    : "res/sound/shopping.mp3"
	},

	//********************合图部分********************
	"bird" : {
		plist		: "res/bird.plist",
		png			: "res/bird.png"
	},

	"enemy" : {
		plist		: "res/enemy.plist",
		png			: "res/enemy.png"
	},

	"gold" : {
		plist       : "res/gold.plist",
		png         : "res/gold.png"
	},
	"magnet" : {
		png         : "res/magnet.png",
		plist       : "res/magnet.plist",
		effect      : "res/magnetEffect.png"
	},
	"panda" : {
		plist       : "res/panda.plist",
		png         : "res/panda.png"
	},
	"platform" : {
		plist       : "res/platform.plist",
		png         : "res/platform.png"
	},
	"shoes" : {
		plist		: "res/shoes.plist",
		png			: "res/shoes.png"
	},
	"redshoes" : {
		plist       : "res/redshoes.plist",
		png         : "res/redshoes.png"
	},

	"font" : {
		fnt	:	"res/font/record-lemon.fnt",
		png :	"res/font/record-lemon.png"
	}
};

var g_resources = [];

for (var i in res.graph) {
	g_resources.push(res.graph[i]);
}

for (var i in res.mode) {
	g_resources.push(res.mode[i]);
}

for (var i in res.bg) {
	g_resources.push(res.bg[i]);
}

for (var i in res.info) {
	g_resources.push(res.info[i]);
}

for (var i in res.rank) {
	g_resources.push(res.rank[i]);
}

for (var i in res.menu) {
	g_resources.push(res.menu[i]);
}

for (var i in res.ui) {
	g_resources.push(res.ui[i]);
}

for (var i in res.open) {
	g_resources.push(res.open[i]);
}

for (var i in res.sound) {
	g_resources.push(res.sound[i]);
}

for (var i in res.bird) {
	g_resources.push(res.bird[i]);
}

for (var i in res.enemy) {
	g_resources.push(res.enemy[i]);
}

for (var i in res.gold) {
	g_resources.push(res.gold[i]);
}

for (var i in res.magnet) {
	g_resources.push(res.magnet[i]);
}

for (var i in res.panda) {
	g_resources.push(res.panda[i]);
}

for (var i in res.platform) {
	g_resources.push(res.platform[i]);
}

for (var i in res.shoes) {
	g_resources.push(res.shoes[i]);
}

for (var i in res.redshoes) {
	g_resources.push(res.redshoes[i]);
}

for (var i in res.font) {
	g_resources.push(res.font[i]);
}

