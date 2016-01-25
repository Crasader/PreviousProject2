#include "CCircle.h"

CCircle::CCircle(void) :
m_center(CCPoint(0, 0)), m_radius(0)
{
}

CCircle::CCircle(cocos2d::CCPoint& center, float radius) :
m_center(center), m_radius(radius){
}

CCircle::~CCircle(void)
{
}

//�ж�Բ�뷽�������Ƿ��ཻ
bool CCircle::intersectsRect(Rect rect) 
{
	int arcR = (int)m_radius;//Բ�ΰ뾶
	int arcOx = (int)m_center.x;//Բ��X����
	int arcOy = (int)m_center.y;//Բ��Y����
	int rectX = (int)rect.getMinX();//���������Ͻ�X����
	int rectY = (int)rect.getMaxY();//���������Ͻ�Y����
	int rectW = rect.getMaxX() - rectX;//�����ο�
	int rectH = rect.getMaxY() - rectY;//�����θ�

	if (((rectX - arcOx) * (rectX - arcOx) + (rectY - arcOy) * (rectY - arcOy)) <= arcR * arcR)
		return true;
	if (((rectX + rectW - arcOx) * (rectX + rectW - arcOx) + (rectY - arcOy) * (rectY - arcOy)) <= arcR * arcR)
		return true;
	if (((rectX - arcOx) * (rectX - arcOx) + (rectY + rectH - arcOy) * (rectY + rectH - arcOy)) <= arcR * arcR)
		return true;
	if (((rectX + rectW - arcOx) * (rectX + rectW - arcOx) + (rectY + rectH - arcOy) * (rectY + rectH - arcOy)) <= arcR * arcR)
		return true;
	//�ֱ��жϾ���4��������Բ�ĵľ����Ƿ�<=Բ�뾶�����<=��˵����ײ�ɹ�


	int minDisX = 0;
	if (arcOy >= rectY && arcOy <= rectY + rectH){
		if (arcOx < rectX)
			minDisX = rectX - arcOx;
		else if (arcOx > rectX + rectW)
			minDisX = arcOx - rectX - rectW;
		else
			return true;
		if (minDisX <= arcR)
			return true;
	}//�жϵ�Բ�ĵ�Y������������ʱX��λ�ã����X��(rectX-arcR)��(rectX+rectW+arcR)�����Χ�ڣ�����ײ�ɹ�

	int minDisY = 0;
	if (arcOx >= rectX && arcOx <= rectX + rectW){
		if (arcOy < rectY)
			minDisY = rectY - arcOy;
		else if (arcOy > rectY + rectH)
			minDisY = arcOy - rectY - rectH;
		else
			return true;
		if (minDisY <= arcR)
			return true;
	}//�жϵ�Բ�ĵ�X������������ʱY��λ�ã����X��(rectY-arcR)��(rectY+rectH+arcR)�����Χ�ڣ�����ײ�ɹ�
	return false;
}

//�ж���Բ�Ƿ��ཻ
bool CCircle::intersectsCircle(CCircle circle) 
{
	//Բ��֮��ľ���С����Բ�뾶֮�ͼ��ཻ
	if (sqrt(pow(m_center.x - circle.m_center.x, 2) + pow(m_center.y - circle.m_center.y, 2)) > m_radius + circle.m_radius) {
		return false;
	}
	return true;
}


bool CCircle::intersectsPoint(Point pos)
{
	auto d = pow(pos.y - m_center.y,2) + pow(pos.x - m_center.x,2);
	return d <= m_radius;
}
CFigure*CCircle::clone()
{
	CCircle*circle = new CCircle(*this);
	return circle;
}

CFigure*CCircle::ApplyAffineTransform(const CFigure* figure, const AffineTransform& anAffineTransform)
{
	auto circle = (CCircle*)figure;

	Vec2 applyOrigin = PointApplyAffineTransform(Vec2(circle->getMCenter().x,circle->getMCenter().y), anAffineTransform);
	

	return new CCircle(applyOrigin,m_radius);
} 
CFigure*CCircle::addposWithFigure(Point pos)
{
	return new CCircle(Point(this->getMCenter() + pos), this->getMRadius());
}

void CCircle::draw(Node*parent)
{
	auto node = DrawNode::create();
	node->drawCircle(getMCenter(), getMRadius(), 360, 1, 1, Color4F::RED);
	parent->addChild(node,100);
}