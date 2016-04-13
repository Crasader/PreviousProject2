#include "utill/FunUtil.h"


bool collision(Rect rectA, Rect rectB)
{
	const float scaleMultiple = 0.7;
	rectA.setRect(rectA.getMinX() + rectA.size.width / 2 * (1 - scaleMultiple), rectA.getMinY() + rectA.size.height / 2 * (1 - scaleMultiple), rectA.size.width*scaleMultiple, rectA.size.height*scaleMultiple);

	rectB.setRect(rectB.getMinX() + rectB.size.width / 2 * (1 - scaleMultiple), rectB.getMinY() + rectB.size.height / 2 * (1 - scaleMultiple), rectB.size.width*scaleMultiple, rectB.size.height*scaleMultiple);

	return rectA.intersectsRect(rectB);
}



bool collision(Sprite*spA, Sprite*spB)
{
	

	const float scaleMultiple = 0.7;
	auto rect1 = spA->getBoundingBox();
	rect1.setRect(rect1.getMinX() + rect1.size.width / 2 * (1 - scaleMultiple), rect1.getMinY() + rect1.size.height / 2 * (1 - scaleMultiple), rect1.size.width*scaleMultiple, rect1.size.height*scaleMultiple);
	auto rect2 = spB->getBoundingBox();
	rect2.setRect(rect2.getMinX() + rect2.size.width / 2 * (1 - scaleMultiple), rect2.getMinY() + rect2.size.height / 2 * (1 - scaleMultiple), rect2.size.width*scaleMultiple, rect2.size.height*scaleMultiple);

	return rect1.intersectsRect(rect2);
}


float  getAngleByPos(Vec2 pos)
{
	auto k = (pos.y - 270.0) / (pos.x - 480);
	if (pos.x>480)
	{
		return 180+CC_RADIANS_TO_DEGREES(atan(k));
	}
	return CC_RADIANS_TO_DEGREES(atan(k));
}


Vec2 CalculateDiffMarginPos(Vec2 pos,float diff)
{
	if (pos.x<=0)
	{
		return Vec2(pos.x - diff, pos.y);
	}
	if (pos.x>=960)
	{
		return Vec2(pos.x + diff, pos.y);
	}
	if (pos.y>=540)
	{
		return Vec2(pos.x, pos.y + diff);
	}
	if (pos.y<=0)
	{
		return Vec2(pos.x, pos.y - diff);
	}

	return pos;
}



float getRandonNumByAtoB(float A, float B)
{	
	return  A + (B - A)*getRand() / (float)RAND_MAX;
}

int getintRandonNumByAtoB(int A, int B, int interval)
{
	auto temp = (B - A) / interval+1;
	return A + interval*(getRand(Server_Seed) % temp);
}


int getCurrencyRankByRange(int startRank, int endRank, int startValue, int endValue, int curValue)
{
	float fTemp = ((float)curValue) / ((float)(endValue - startValue));
	auto currrRank = endRank - (endRank - startRank)*fTemp;
	return currrRank;
}

std::string SpliceDataForPostHttp(std::vector<std::string> strs)
{
	std::string s;
	for (auto var:strs)
	{
		s += "&";
		s += var.c_str();
	}
	return s;
}

std::string  SpliceDataForPostHttp(std::string str1, ...)
{

	return "";
}

std::string NewAtoI(int num)
{
	auto str = String::createWithFormat("%d", num);
	return str->getCString();
}
std::string NewAtoI(long num)
{
	auto str = String::createWithFormat("%ld", num);
	return str->getCString();
}


std::string myWrap(std::string str, int length)
{
	unsigned int beginPos = 0;  //字符串的初始位置
	std::string resultStr;		//返回的字符串


	std::vector<std::string > str_vec;  //创建一个字符串类型的顺序容器
	do
	{
		str_vec.push_back(str.substr(beginPos, length)); //substr函数的作用类似剪刀，将str中从beginPos到length之间的字符串剪下来，单独放入容器中 
		if (beginPos + length > str.size())
		{
			break;  //当要裁剪的长度超出str的长度，则退出循环
		}
		else
		{
			beginPos += length;
		}

	} while (true);

	for (unsigned int i = 0; i < str_vec.size(); ++i)
	{
		resultStr.append(str_vec.at(i)).append("\n"); //从容器逐一取出之前裁剪好的一段段字符串，分别在字符串后面加上换行符。append()类似胶水，将\n粘到字符串后面 
	}


	//   resultStr.pop_back();  //这一句是将最后一个多余的\n给删掉


	return resultStr;
}

int getRandValueInVec(std::vector<int> vec)
{
	int size = vec.size();
	return vec.at(getRand(Server_Seed) % size);
}

Action* getForeverAcByNameAndInterval(const char* name, float interval)
{
	auto ac = RepeatForever::create(Sequence::create(DelayTime::create(interval), AnimationUtil::getInstance()->getAnimate(name), nullptr)); 
		return ac;

}

float getTurretRotation(Point start_pos, Point pos){
	//计算两点之间的角度


	return 270-CC_RADIANS_TO_DEGREES((start_pos-pos).getAngle());

}

unsigned long getCurrentTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int getRand(unsigned int _Seed)
{
	srand(_Seed);
	return rand();
}



bool line_rect_intersection(Point start_p, Point end_p, Rect rect)
{
	int a = start_p.y - end_p.y;
	int b = end_p.x - start_p.x;
	int c = start_p.x* end_p.y - end_p.x* start_p.y;

	int left = rect.getMinX();
	int top = rect.getMaxY();
	int right = rect.getMaxX();
	int bottom = rect.getMinY();

	////思路:先看线段所在直线是否与矩形相交，如果不相交则必为 “Ｆ”，
	////如果相交，则看线段的两个点是否在矩形的同一边（即两点的 x（y)  坐标都比矩形的小 x(y) 坐标小，或者大）,
	////若在同一边则为“Ｆ”，否则就是相交的情况。
	if ((a* left + b*top + c >= 0 && a* right + b* bottom + c <= 0) ||
		(a* left + b*top + c <= 0 && a* right + b* bottom + c >= 0) ||
		(a* left + b*bottom + c >= 0 && a* right + b* top + c <= 0) ||
		(a* left + b*bottom + c >= 0 && a* right + b* top + c <= 0))
	{
		if ((start_p.x < left && end_p.x < left) ||
			(start_p.x > right && end_p.x < left) ||
			(start_p.y > top && end_p.y > top) ||
			(start_p.y < bottom && end_p.y < bottom))  ///判断线段是否在矩形一侧
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}