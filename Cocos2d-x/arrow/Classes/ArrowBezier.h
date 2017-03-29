/**
* Created by HAO on 2016/9/5.
*/

#pragma once

#ifndef __ArrowBezier__
#define __ArrowBezier__

#include "cocos2d.h"

using namespace cocos2d;

typedef struct _QuadBezierConfig {
	
	Point controlPoint;
	Point endPoint;
}QuadBezierConfig;

class ArrowBezier : public BezierBy {

public:
	ArrowBezier ();
	~ArrowBezier ();
	static ArrowBezier* creat (float t, const QuadBezierConfig& config);
	bool initWithDuration (float t, const QuadBezierConfig& config);
	virtual void update (float time);

private:
	QuadBezierConfig _config;
};

#endif /* defined(__ArrowBezier__) */
