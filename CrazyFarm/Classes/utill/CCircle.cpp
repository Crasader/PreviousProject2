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

//判断圆与方形区域是否相交
bool CCircle::intersectsRect(Rect rect) 
{
	int arcR = (int)m_radius;//圆形半径
	int arcOx = (int)m_center.x;//圆心X坐标
	int arcOy = (int)m_center.y;//圆心Y坐标
	int rectX = (int)rect.getMinX();//长方形左上角X坐标
	int rectY = (int)rect.getMaxY();//长方形右上角Y坐标
	int rectW = rect.getMaxX() - rectX;//长方形宽
	int rectH = rect.getMaxY() - rectY;//长方形高

	if (((rectX - arcOx) * (rectX - arcOx) + (rectY - arcOy) * (rectY - arcOy)) <= arcR * arcR)
		return true;
	if (((rectX + rectW - arcOx) * (rectX + rectW - arcOx) + (rectY - arcOy) * (rectY - arcOy)) <= arcR * arcR)
		return true;
	if (((rectX - arcOx) * (rectX - arcOx) + (rectY + rectH - arcOy) * (rectY + rectH - arcOy)) <= arcR * arcR)
		return true;
	if (((rectX + rectW - arcOx) * (rectX + rectW - arcOx) + (rectY + rectH - arcOy) * (rectY + rectH - arcOy)) <= arcR * arcR)
		return true;
	//分别判断矩形4个顶点与圆心的距离是否<=圆半径；如果<=，说明碰撞成功


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
	}//判断当圆心的Y坐标进入矩形内时X的位置，如果X在(rectX-arcR)到(rectX+rectW+arcR)这个范围内，则碰撞成功

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
	}//判断当圆心的X坐标进入矩形内时Y的位置，如果X在(rectY-arcR)到(rectY+rectH+arcR)这个范围内，则碰撞成功
	return false;
}

//判断两圆是否相交
bool CCircle::intersectsCircle(CCircle circle) 
{
	//圆心之间的距离小于两圆半径之和即相交
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