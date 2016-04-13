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
	unsigned int beginPos = 0;  //�ַ����ĳ�ʼλ��
	std::string resultStr;		//���ص��ַ���


	std::vector<std::string > str_vec;  //����һ���ַ������͵�˳������
	do
	{
		str_vec.push_back(str.substr(beginPos, length)); //substr�������������Ƽ�������str�д�beginPos��length֮����ַ������������������������� 
		if (beginPos + length > str.size())
		{
			break;  //��Ҫ�ü��ĳ��ȳ���str�ĳ��ȣ����˳�ѭ��
		}
		else
		{
			beginPos += length;
		}

	} while (true);

	for (unsigned int i = 0; i < str_vec.size(); ++i)
	{
		resultStr.append(str_vec.at(i)).append("\n"); //��������һȡ��֮ǰ�ü��õ�һ�ζ��ַ������ֱ����ַ���������ϻ��з���append()���ƽ�ˮ����\nճ���ַ������� 
	}


	//   resultStr.pop_back();  //��һ���ǽ����һ�������\n��ɾ��


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
	//��������֮��ĽǶ�


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

	////˼·:�ȿ��߶�����ֱ���Ƿ�������ཻ��������ཻ���Ϊ ���ơ���
	////����ཻ�����߶ε��������Ƿ��ھ��ε�ͬһ�ߣ�������� x��y)  ���궼�Ⱦ��ε�С x(y) ����С�����ߴ�,
	////����ͬһ����Ϊ���ơ�����������ཻ�������
	if ((a* left + b*top + c >= 0 && a* right + b* bottom + c <= 0) ||
		(a* left + b*top + c <= 0 && a* right + b* bottom + c >= 0) ||
		(a* left + b*bottom + c >= 0 && a* right + b* top + c <= 0) ||
		(a* left + b*bottom + c >= 0 && a* right + b* top + c <= 0))
	{
		if ((start_p.x < left && end_p.x < left) ||
			(start_p.x > right && end_p.x < left) ||
			(start_p.y > top && end_p.y > top) ||
			(start_p.y < bottom && end_p.y < bottom))  ///�ж��߶��Ƿ��ھ���һ��
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