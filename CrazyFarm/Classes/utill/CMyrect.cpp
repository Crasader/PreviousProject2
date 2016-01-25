#include "CMyrect.h"

CMyrect::CMyrect()
{

}

CMyrect::CMyrect(Rect rect)
{
	origin = rect.origin;
	size = rect.size;
}


CMyrect::CMyrect(Point orgin, Size ssize)
{
	origin = orgin;
	size = ssize;
}
bool CMyrect::intersectsRect(Rect rect)
{
	return Rect::intersectsRect(rect);
}

bool CMyrect::intersectsPoint(Point pos)
{
	return Rect::containsPoint(pos);
}
CFigure* CMyrect::clone()
{
	CMyrect*rect = new CMyrect(*this);
	return rect;
}

CFigure*CMyrect::ApplyAffineTransform(const CFigure* figure, const AffineTransform& anAffineTransform)
{
	auto rect = (CMyrect*)figure;

	return new CMyrect(RectApplyAffineTransform(*rect, anAffineTransform));
}

CFigure*CMyrect::addposWithFigure(Point pos)
{
	return new CMyrect(Point(origin + pos), size);
}

void CMyrect::draw(Node*parent)
{
	auto node = DrawNode::create();
	node->drawRect(origin,Point(this->getMaxX(),getMaxY()),Color4F::RED);
	parent->addChild(node,100);
}

bool CMyrect::intersectsCircle(CCircle circle)
{
	int arcR = (int)circle.getMRadius();//圆形半径
	int arcOx = (int)circle.getMCenter().x;//圆心X坐标
	int arcOy = (int)circle.getMCenter().y;//圆心Y坐标
	int rectX = (int)getMinX();//长方形左上角X坐标
	int rectY = (int)getMaxY();//长方形右上角Y坐标
	int rectW = getMaxX() - rectX;//长方形宽
	int rectH = getMaxY() - rectY;//长方形高

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