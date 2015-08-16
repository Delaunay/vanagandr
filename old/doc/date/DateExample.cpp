#include "../date/Date.h"


namespace vanagandr
{
	Day Date::dayElapsed(Year AAAA, Month MM, Day DD, Year Start)
	{
		unsigned int i = 0;
		unsigned int r = DD;

		if(AAAA % 4 == 0)
			i = 1;

		switch(MM)
		{
		case 1:
			r += 0;
			break;
		case 2:
			r += 31;
			break;
		case 3:
			r += 59 + i;
			break;
		case 4:
			r += 90 + i;
			break;
		case 5:
			r += 120 + i;
			break;
		case 6:
			r += 151 + i;
			break;
		case 7:
			r += 181 + i;
			break;
		case 8:
			r += 212 + i;
			break;
		case 9:
			r += 243 + i;
			break;
		case 10:
			r += 273 + i;
			break;
		case 11:
			r += 304 + i;
			break;
		case 12:
			r += 334 + i;
			break;
		default:
			r += 0;
			break;
		}

		for(int i = 0, n = AAAA - Start; i < n; i++)
		{
			if( (Start + i) % 4 == 0)
				r += 366;
			else
				r += 365;
		}

		return r;
	}

Periods Date::n(Date Mat, Date Today, YearInDays a)
{
	double y1, y2;

	if ( a == Y360)
	{
		y1 = 360;
		y2 = 360;
	}
	else if (a == Y365)
	{
		y1 = 365;
		y2 = 365;
	}
	else if (a == Y36525)
	{
		y1 = 365.25;
		y2 = 365.25;
	}
	else if (a == Y366)
	{
		y1 = 366;
		y2 = 366;
	}
	else
	{
		y1 =  365 + Date::isLeap(Mat  .year());
		y2 =  365 + Date::isLeap(Today.year());

	}

	Periods dif =		+   Mat.year() - Today.year();
			dif = dif	+ ( Mat  .dayOfYear() + Mat  .timeOfDay() / double(DAY)  ) / y1 ;
			dif = dif	- ( Today.dayOfYear() + Today.timeOfDay() / double(DAY)  ) / y2 ;

	return dif;
}

Periods Date::n(Date Today, YearInDays a)
{
	//*
	return Date::n(*this, Today, a);
	/*///
	double y1, y2;

	if ( a == FIN::Y360)
	{
		y1 = 360;
		y2 = 360;
	}
	else if (a == FIN::Y365)
	{
		y1 = 365;
		y2 = 365;
	}
	else if (a == FIN::Y36525)
	{
		y1 = 365.25;
		y2 = 365.25;
	}
	else if (a == FIN::Y366)
	{
		y1 = 366;
		y2 = 366;
	}
	else
	{
		y1 =  365 + Date::isLeap(this->year());
		y2 =  365 + Date::isLeap(Today.year());

	}

	Periods dif =		+   this->year() - Today.year();
			dif = dif	+ ( this->dayOfYear() + this->timeOfDay() / (double) FIN::DAY  ) / y1 ;
			dif = dif	- ( Today.dayOfYear() + Today.timeOfDay() / (double) FIN::DAY  ) / y2 ;

	return dif;//*/
}
}
