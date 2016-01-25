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
	int arcR = (int)circle.getMRadius();//Բ�ΰ뾶
	int arcOx = (int)circle.getMCenter().x;//Բ��X����
	int arcOy = (int)circle.getMCenter().y;//Բ��Y����
	int rectX = (int)getMinX();//���������Ͻ�X����
	int rectY = (int)getMaxY();//���������Ͻ�Y����
	int rectW = getMaxX() - rectX;//�����ο�
	int rectH = getMaxY() - rectY;//�����θ�

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