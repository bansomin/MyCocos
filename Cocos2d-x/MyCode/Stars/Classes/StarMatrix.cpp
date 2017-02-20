//
//  StarMatrix.cpp
//  Stars
//
//  Created by HAO on 15-7-18.
//
//
/*
    * StarMatrix是对一个Stars*二维数组的包装
    * init()函数会调用initMatrix()方法,面initMatrix()方法实质就是初始化内置的Stars*二维数组
    * 初始化的时候同时对Stars的一些属性进行设置(当前位置,目标位置,在矩阵中的位置)
    * isEnded():判断是否能继续下去（遍历每一个星星,如果上下左右都没有与之相同颜色,判定游戏结束。开始把剩下的两两互不相连的星星消去）
    * 
*/


#include <ctime>
#include "Audio.h"
#include "GameData.h"
#include "ComboEffect.h"
#include "StarParticle.h"

extern bool isMusic;
extern bool isSound;
extern bool isModel;

#include "StarMatrix.h"

float StarMatrix::_ONE_CLEAR_TIME = 0.05f;

StarMatrix* StarMatrix::create(GameScene* scene){
    
    StarMatrix* ret = new StarMatrix();
    
    if (ret && ret->init(scene)) {
        
        ret->autorelease();
        
        return ret;
    }
    CC_SAFE_DELETE(ret);
    
    return nullptr;
}

bool StarMatrix::init(GameScene* scene){
    
    if (!Node::init()) {
        
        return false;
    }
    
    _winSize = Director::getInstance()->getWinSize();
    
    _my_scene   = scene;
    _needClear = false;
    _clearSumTime = 0;  //累加器
        
    //？？？？
    memset(_stars, 0,sizeof(Stars*) * _ROW_NUM * _COL_NUM);
    
//调用initMatrix()
    initMatrix();
    
    return true;
}

void StarMatrix::initMatrix(){
    
//随机颜色
    srand(time(0));
    
    for (int i = 0; i<_ROW_NUM; i++) {
        for (int j = 0; j<_COL_NUM; j++) {
            
            int color = abs(rand()%Stars::_COLOR_MAX_NUM);  //Stars::COLOR_MAX_NUM = 5
            if (color < 0){
            
            }
            
            Stars* tempStar = Stars::create(color);
            
            _stars[i][j] = tempStar;
            
            tempStar->setPosition(getPositionByIndex(i, j) + Point(0, 32));
            tempStar->setDesPosition(getPositionByIndex(i, j));
            tempStar->setIndex_IJ(i, j);
            
//利用isModel进行判断,精灵缩放的比例
            if (isModel) {
                tempStar->setScale(0.307f); //心缩放
            }
            else{
                tempStar->setScale(1.35f); //星星缩放
            }
            
            this->addChild(tempStar);
        }
    }
}

//getPositionByIndex:由矩阵位置i和j得到一个Point函数（由i和j得到像素位置的方法）
Point StarMatrix::getPositionByIndex(int i, int j){
    
    //控制显示宽度
    float x = j * Stars::_STAR_WIDTH + Stars::_STAR_WIDTH/2;
    //float x = j * _winSize.width/10 + _winSize.width/10/2;
    //控制显示高度
    float y = (StarMatrix::_COL_NUM - i)*Stars::_STAR_HEIGHT - Stars::_STAR_HEIGHT/2;
    //float y = (StarMatrix::_COL_NUM - i)*_winSize.width/10 - _winSize.width/10/2;
    
    return Point(x, y);
}

/*
    * 星星一个一个的消失
    * delta:上一帧到下一帧的间隔时间,到达一定时间后消除星星
*/
void StarMatrix::updateStar(float delta){
    
    for (int i = 0; i<_ROW_NUM; i++) {
        for (int j = 0; j<_COL_NUM; j++) {
            
            if (_stars[i][j] != nullptr) {
                //进入到Stars中进行调整位置
                _stars[i][j]->updatePosition();
            }
        }
    }
    
    if (_needClear) {
        _clearSumTime += delta;
        if (_clearSumTime > _ONE_CLEAR_TIME) {   //0.05f
            //消除
            clearMatrixOneByOne();
            _clearSumTime = 0;
        }
    }
}

void StarMatrix::clearMatrixOneByOne(){
    
    for(int i=0;i<_ROW_NUM;i++){
		for(int j=0;j<_COL_NUM;j++){
			if(_stars[i][j] == nullptr)
				continue;
            
			showStarParticleEffect(_stars[i][j]->getColor(),_stars[i][j]->getPosition(),this);            
            
			_stars[i][j]->removeFromParentAndCleanup(true);
			_stars[i][j] = nullptr;
			return;
		}
	}
	//ƒ‹πª÷¥––µΩ’‚“ªæ‰Àµ√˜Matrix»´Œ™ø’£¨≤ª‘⁄–Ë“™«Âø’
	_needClear = false;
    
	//如果当前分数大于需要分数
	if(GAMEDATA::getInstance()->getCurScore() >= GAMEDATA::getInstance()->getNextScore()){
		GAMEDATA::getInstance()->setCurLevel(GAMEDATA::getInstance()->getCurLevel() + 1);
        
        //进入下一关
		_my_scene->gotoNextLevel();
        
        GAMEDATA::getInstance()->saveCurLevelScore(GAMEDATA::getInstance()->getCurLevel(), GAMEDATA::getInstance()->getCurScore());
        
	}else{
		_my_scene->gotoGameOver();
		CCLOG("GAME OVER");
	}
}


bool StarMatrix::isEnded(){
    
    bool bRet = true;
    for (int i = 0; i<_ROW_NUM; i++) {
        for (int j = 0; j<_COL_NUM; j++) {
            
                if (_stars[i][j] == nullptr)
                continue;
                int curColor = _stars[i][j]->getColor();
                
                //上
                if (i-1>=0 && _stars[i-1][j] != nullptr && _stars[i-1][j]->getColor() == curColor) {
                    return false;
                }
                
                //下
                if (i+1 < _ROW_NUM && _stars[i+1][j] != nullptr && _stars[i+1][j]->getColor() == curColor) {
                    return false;
                }
                
                //左
                if (j-1 >= 0 && _stars[i][j-1] != nullptr && _stars[i][j-1]->getColor() == curColor) {
                    return false;
                }
                
                //右
                if (j+1 < _COL_NUM && _stars[i][j+1] != nullptr && _stars[i][j+1]->getColor() == curColor) {
                    return false;
                }
            }
        }
    return bRet;
}

//刷新显示分数
void StarMatrix::refreshScore(){
    
    GAMEDATA* data = GAMEDATA::getInstance();
    data->setCurScore(data->getCurScore() + selectedList.size()*selectedList.size()*5);
    if (data->getCurScore() > data->getHistoryScore()) {
        
        data->setHistoryScore(data->getCurScore());
    }
    _my_scene->refreshMenu();
}

//得到剩下的星星数目
int  StarMatrix::getLeftStarNum(){
    
    int ret = 0;
    for (int i = 0; i<_ROW_NUM; i++) {
        for (int j = 0; j<_COL_NUM; j++) {
            
            if (_stars[i][j] == nullptr)
                continue;
            ret ++;
        }
    }
    return ret;
}

//得到一串连接的星星的函数（广度优先遍历法）
/*
    *1、把被点击的星星放到遍历队列
    *2、分别对遍历队列里面的元素进行如下操作
    ** 把该元素放进待删除的列表（就是我们要的列表）
    ** 看看上方是否有相同颜色的星星,如果有,把上方的星星放到遍历队列
    ** 看看下方是否有相同颜色的星星,如果有,把上方的星星放到遍历队列
    ** 看看左边是否有相同颜色的星星,如果有,把上方的星星放到遍历队列
    ** 看看右边是否有相同颜色的星星,如果有,把上方的星星放到遍历队列
    *3、遍历队列队头疼出列,得到新的队头
    *重复2步
*/

void StarMatrix::getSelectedList(Stars* star){
    
    selectedList.clear();
	deque<Stars*> travelList;
	travelList.push_back(star);
	deque<Stars*>::iterator it;
    
	for(it= travelList.begin();it != travelList.end();){
		Stars* star = *it;
		Stars* linkStar = nullptr;
		int index_i = star->getIndexI();
		int index_j = star->getIndexJ();
		//…œ
		if(index_i-1 >= 0 && (linkStar = _stars[index_i-1][index_j]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(_stars[index_i-1][index_j]);
		}
		//œ¬
		if(index_i+1 < _ROW_NUM  && (linkStar = _stars[index_i+1][index_j]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(_stars[index_i+1][index_j]);
		}
		//◊Û
		if(index_j-1 >= 0 && (linkStar = _stars[index_i][index_j-1]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(_stars[index_i][index_j-1]);
		}
		//”“
		if(index_j+1 < _COL_NUM && (linkStar = _stars[index_i][index_j+1]) ){
			if(!linkStar->isSelected() && linkStar->getColor() == star->getColor())
				travelList.push_back(_stars[index_i][index_j+1]);
		}
		if(!star->isSelected()){
			star->setSelected(true);
			selectedList.push_back(star);
		}
		travelList.pop_front();
		it = travelList.begin();
	}
    
    
/*
    selectedList.clear();   //每次点击时,先把待删除列表清空
    deque<Stars*>traveList; //遍历队列
    traveList.push_back(star);  //把点击的星星放进遍历队列
    
    deque<Stars*>::iterator it;
    
    for (it = traveList.begin(); it != traveList.end();) { //当遍历队列为空的时候停止
        Stars* tempStar = *it;
        Stars* linkStar = nullptr;
        
        int index_i = tempStar->getIndexI();
        int index_j = tempStar->getIndexJ();
        
        //上
        if (index_i-1 >= 0 && (linkStar = _stars[index_i-1][index_j])) {  //判断是否越界
            if (!linkStar->isSelected() && linkStar->getColor() == tempStar->getColor()) {  //判断是否已经被纳入选择队列并且与遍历队列的星星颜色一样
                
                traveList.push_back(_stars[index_i-1][index_j]);    //如果没有被纳入选择队列,并且颜色一样就加入到遍历队列中
            }
        }
        
        //上
        if (index_i+1 < _ROW_NUM && (linkStar = _stars[index_i+1][index_j])) {
            if (!linkStar->isSelected() && linkStar->getColor() == tempStar->getColor()) {
                
                traveList.push_back(_stars[index_i+1][index_j]);
            }
        }
        
        //左
        if (index_j-1 >= 0 && (linkStar = _stars[index_i][index_j-1])) {
            if (!linkStar->isSelected() && linkStar->getColor() == tempStar->getColor()) {
                
                traveList.push_back(_stars[index_i][index_j-1]);
            }
        }
        
        //右
        if (index_j+1 < _COL_NUM && (linkStar = _stars[index_i][index_j+1])) {
            if (!linkStar->isSelected() && linkStar->getColor() == tempStar->getColor()) {
                
                traveList.push_back(_stars[index_i][index_j+1]);
            }
        }
        
        if (!tempStar->isSelected()) {  //处理当前的星星
            tempStar->setSelected(true);    //设置已经被加入到选择队列（待删除队列）
            selectedList.push_back(tempStar);   //加入到选择队列(待删除队列)
        }
        
        traveList.pop_front();  //队头出队
        it = traveList.begin(); //得到新的队头
    }
 */
}


//删除一串连接的星星的函数
void StarMatrix::deleteSelectedList(){
    
    if(selectedList.size() <= 1){
		_my_scene->hideLinkNum();
		selectedList.at(0)->setSelected(false);
		return;
	}
    
	for(auto it = selectedList.begin();it != selectedList.end();it++){
		Stars* star = *it;
		//¡£◊”–ßπ˚
        showStarParticleEffect(star->getColor(), star->getPosition(), this);
		_stars[star->getIndexI()][star->getIndexJ()] = nullptr;
		star->removeFromParentAndCleanup(true);
    
		//≤•∑≈“Ù–ß
        
        if (isSound) {
            Audio::getInstance()->playEffects();
        }
	}
	//COMBO–ßπ˚
	showComboEffect(selectedList.size(),this);

    
    if (isSound) {
       Audio::getInstance()->playCombo(selectedList.size());
    }

	refreshScore();
    
	_my_scene->showLinkNum(selectedList.size());
    
	adjustMatrix();
    
	if(isEnded()){
		_my_scene->floatLeftStarMsg(getLeftStarNum());
	}
}

//重新进行位置调整
void StarMatrix::adjustMatrix(){
    
    //¥π÷±∑ΩœÚµ˜’˚
	for(int i = _ROW_NUM-1;i>=0;i--){
		for(int j = _COL_NUM-1;j>=0;j--){
			if(_stars[i][j] == nullptr){
				int up = i;
				int dis = 0;
				while(_stars[up][j] == nullptr){
					dis++;
					up--;
					if(up<0){
						break;
					}
				}
				
				for(int begin_i = i - dis;begin_i >= 0;begin_i--){
					if(_stars[begin_i][j] == nullptr)
						continue;
					Stars* s = _stars[begin_i + dis][j] = _stars[begin_i][j];
					s->setIndex_IJ(begin_i + dis,j);
					s->setDesPosition(getPositionByIndex(begin_i + dis,j));
					_stars[begin_i][j] = nullptr;
				}
			}else{
				continue;
			}
		}
	}
	//ÀÆ∆Ω∑ΩœÚµ˜’˚
	for(int j = 0;j < _COL_NUM;j++){
		if(_stars[_ROW_NUM-1][j] == nullptr){
			int des = 0;
			int right = j;
			while(_stars[_ROW_NUM-1][right] == nullptr){
				des++;
				right++;
			}
			for(int begin_i = 0;begin_i<_ROW_NUM;begin_i++){
				for(int begin_j = j + des;begin_j < _COL_NUM;begin_j++){
					if(_stars[begin_i][begin_j] == nullptr)
						continue;
					Stars* s = _stars[begin_i][begin_j - des] = _stars[begin_i][begin_j];
					s->setIndex_IJ(begin_i,begin_j - des);
					s->setDesPosition(getPositionByIndex(begin_i,begin_j - des));
					_stars[begin_i][begin_j] = nullptr;
				}
			}
		}
	}
    
/*
    //垂直方向
    for (int i = _ROW_NUM-1; i>=0; i--) {
        for (int j = _COL_NUM-1; j>=0; j--) {
            if (_stars[i][j] == nullptr) {
                int up  = i;
                int dis = 0;
                while (_stars[up][j] == nullptr) {
                    dis++;
                    up--;
                    if (up<0) {
                        break;
                    }
                }
                
                for (int begin_i = i-dis; begin_i>=0; begin_i--) {
                    if (_stars[begin_i][j] == nullptr)
                        continue;
                    
                    Stars* tempStar = _stars[begin_i+dis][j] = _stars[begin_i][j];
                    tempStar->setIndex_IJ(begin_i+dis, j);
                    tempStar->setDesPosition(getPositionByIndex(begin_i+dis, j));
                    _stars[begin_i][j] = nullptr;
                }
            }
            else{
                continue;
            }
        }
    }
    
    //竖直方向
    for (int j = 0; j<_COL_NUM; j++) {
        if (_stars[_ROW_NUM-1][j] == nullptr) {
            int des   = 0;
            int right = j;
            
            while (_stars[_ROW_NUM-1][right] == nullptr) {
                des ++;
                right ++;
            }
            
            for (int begin_i = 0; begin_i<_ROW_NUM; begin_i++) {
                for (int begin_j = j+des; begin_j<_COL_NUM; begin_j++) {
                    if (_stars[begin_i][begin_j-des])
                        continue;
                    
                    Stars* tempStar = _stars[begin_i][begin_j-des] = _stars[begin_i][begin_j];
                    tempStar->setIndex_IJ(begin_i, begin_j-des);
                    tempStar->setDesPosition(getPositionByIndex(begin_i, begin_j-des));
                    
                    _stars[begin_i][begin_j] = nullptr;
                }
            }
        }
    }
 */
}

//由GameOver中的onTouchBegan()传过来的触摸点的入口
void StarMatrix::onTouch(const Point& point){
    
    //得到触摸点的星星在矩阵中的位置。
    Stars* tempStar = getStarByTouch(point);
    
    if (tempStar) {
        getSelectedList(tempStar);
        deleteSelectedList();
    }
}

//被点击的星星在矩阵中的位置(像素与矩阵坐标的转换)
Stars* StarMatrix::getStarByTouch(const Point& p){
    
    int k = p.y / Stars::_STAR_HEIGHT;
   // int k = p.y / _winSize.width/10;
    
    int i = _ROW_NUM - 1 - k;
    
    int j = p.x / Stars::_STAR_WIDTH;
    //int j = p.x / _winSize.width/10;
    
    if (i >= 0 && i < _ROW_NUM &&
        j >= 0 && j < _COL_NUM &&
        _stars[i][j] != nullptr) {
        
        return _stars[i][j];
    }
    else{
        return nullptr;
    }
}

void StarMatrix::setNeedClear(bool b){
    
    _needClear = b;
}








