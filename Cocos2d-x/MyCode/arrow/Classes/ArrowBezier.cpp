/**
* Created by HAO on 2016/9/5.
*/

#include "ArrowBezier.h"

// ԭ�����������ߵļ��㹫ʽ
// Bezier cubic formula:
//    ((1 - t) + t)3 = 1
// Expands to
//   (1 - t)3 + 3t(1-t)2 + 3t2(1 - t) + t3 = 1
ArrowBezier::ArrowBezier () {

};

ArrowBezier::~ArrowBezier () {

};

static inline float bezierat (float a, float b, float c, float d, float t) {

	return (powf (1 - t, 3) * a +
			3.0f*t*(powf (1 - t, 2))*b +
			3.0f*powf (t, 2)*(1 - t)*c +
			powf (t, 3)*d);
};

static inline float bezierat1 (float a, float b, float d, float t) {
	
	return (powf (1 - t, 2) * a +
			2.0f*t*(1 - t)*b +
			powf (t, 2)*d);
};

ArrowBezier* ArrowBezier::creat (float t, const QuadBezierConfig& config) {

	ArrowBezier* bezier = new ArrowBezier ();
	bezier->initWithDuration (t, config);
	bezier->autorelease ();

	return bezier;
};

bool ArrowBezier::initWithDuration (float t, const QuadBezierConfig& config) {

	if (ActionInterval::initWithDuration(t)) {
		_config = config;
		log ("ArrowBezier_control = %f, %f", _config.controlPoint.x, _config.controlPoint.y);
		log ("ArrowBezier_endPoint = %f, %f", _config.endPoint.x, _config.endPoint.y);

		return true;
	}
	return false;
};

void ArrowBezier::update (float time) {

	if (_target) {
		float xa = 0;
		float xb = _config.controlPoint.x;
		float xd = _config.endPoint.x;

		float ya = 0;
		float yb = _config.controlPoint.y;
		float yd = _config.endPoint.y;

		float x = bezierat1 (xa, xb, xd, time);
		float y = bezierat1 (ya, yb, yd, time);

#if CC_ENABLE_STACKABLE_ACTIONS
		/*
		�������, �ı�λ�����ԵĶ���(�� MoveBy, JumpBy, BezierBy..)����ŵ�ջ����.
		�����һ������(node)��ͬʱ������2�������ı�λ�����ԵĶ���, �������(node)������λ�û������иı�λ�����Զ�����ʸ����. �������, ֻ�����һ���ı�λ�����ԵĶ�������Ч.
		Ĭ������. ������Ϊ�˺�v2.0����ɵİ汾����.
		*/

		Vec2 currentPos = _target->getPosition ();
		Vec2 diff = currentPos - _previousPosition;
		_startPosition = _startPosition + diff;

		Vec2 newPos = _startPosition + Vec2 (x, y);
		_target->setPosition (newPos);

		_previousPosition = newPos;

		if (0 != time) {
			Vec2 vector = currentPos - newPos;
			float radians = vector.getAngle ();
			float degrees = CC_RADIANS_TO_DEGREES (-1 * radians);
			_target->setRotation (degrees - 180);
		}

#else
		_target->setPosition (_startPosition + Vec2 (x, y));
#endif // !CC_ENABLE_STACKABLE_ACTIONS

	}
}