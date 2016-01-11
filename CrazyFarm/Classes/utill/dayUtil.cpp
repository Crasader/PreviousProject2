#include "dayUtil.h"

#include "network/HttpRequest.h"

#include <cstdio>

USING_NS_CC;
using namespace network;
using namespace std;



SystemTime::SystemTime(const string &formatString)
{
	// Format: 2015-08-19 17:51:36
	int num = sscanf(formatString.c_str(), "%d-%d-%d",
		&_year, &_month, &_day);

	_formatString = formatString;
}

SystemTime::~SystemTime()
{
}
int SystemTime::getYear() const
{
	return _year;
}

int SystemTime::getMonth() const
{
	return _month;
}

int SystemTime::getDay() const
{
	return _day;
}

const std::string& SystemTime::getFormatString() const
{
	return _formatString;
}

bool SystemTime::isContinuousByAandB(SystemTime*dayA, SystemTime*dayB)
{
	///同年
    if (dayB->getYear() == dayB->getYear())
    {
		///同月
		if (dayA->getMonth()==dayB->getMonth())
		{
			if (dayB->getDay()-dayA->getDay() == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//不同月
		else
		{
			//上下月
			if (dayB->getMonth()-dayA->getMonth()==1)
			{
				if (dayB->getDay()+getDayBymonthandyear(dayA->getYear(),dayA->getMonth())-dayA->getDay()==1)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
    }
	//不同年
	else
	{
		//上下年
		if (dayB->getYear() - dayA->getYear() == 1)
		{
			if (dayB->getDay() + getDayByyear(dayA->getYear()) - dayA->getDay() == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}




int getDayBymonthandyear(int year, int month)
{
	switch (month)
	{
	case 1:
	case 5:
	case 3:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
		break;
	case 2:
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
		{
			return 29;
		}
		else
		{
			return 28;
		}
	default:
		return -1;
		break;
	}
}

int getDayByyear(int year)
{
	if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0)
	{
		return 366;
	}
	else
	{
		return 365;
	}
}