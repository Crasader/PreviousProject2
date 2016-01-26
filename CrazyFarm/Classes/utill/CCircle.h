#pragma once
#include "cocos2d.h"
#include "utill/CFigure.h"
USING_NS_CC;

class CCircle:public CFigure
{
public:
	CCircle(void);
	CCircle(Point center, float radius); //�ṩԲ����뾶 ��ʼ��Բ
	~CCircle(void);

	bool intersectsRect(Rect rect) ;//�Ƿ��볤���������ཻ
	bool intersectsCircle(CCircle circle);//�Ƿ���Բ�������ཻ
	bool intersectsPoint(Point pos);
	virtual CFigure* ApplyAffineTransform(const CFigure* figure, const AffineTransform& anAffineTransform);
	virtual CFigure* addposWithFigure(Point pos);
	virtual void draw(Node*parent);
	CFigure*clone();
private:
	CC_SYNTHESIZE(Point, m_center, MCenter);//Բ��
	CC_SYNTHESIZE(float, m_radius, MRadius);//�뾶
};


