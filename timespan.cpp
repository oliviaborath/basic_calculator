#include "timespan.h"

#include <cmath>
#include<iomanip>
#include <iostream>

// print out the timespan in hr:min:second format
// handle the leading zeros
ostream &operator<<(ostream &out, const TimeSpan &ts) 
{ 
    // append negative sign to hour 
    // if hour and minute are both zero and second is negative
    if(ts.getHour() == 0 && (ts.getMinute() < 0 || ts.getSecond() < 0))
    {
        out << "-" << ts.getHour() << ":" << setw(2) << setfill('0') << 
        ts.getMinute() << ":" << setw(2) << setfill('0') << ts.getSecond() * (-1);
        return out;
    }
    // turn minute and second to positive value
    // if minute or second given are negative
    if(ts.getSecond() < 0 || ts.getMinute() < 0) 
    {
        out << ts.getHour() << ":" << setw(2) << setfill('0') << 
        ts.getMinute() * (-1) << ":" << setw(2) << setfill('0') << ts.getSecond() * (-1);
        return out;
    }
    else 
    {
        out << ts.getHour() << ":" << setw(2) << setfill('0') << 
        ts.getMinute() << ":" << setw(2) << setfill('0') << ts.getSecond();
        return out; 
    }
}

// explicit TimeSpan(int Hour = 0, int Minute = 0, int Second = 0);
// constructor to take three parameters 
TimeSpan::TimeSpan(double hour, double minute, double second) 
{
   //setTime Double(hour, minute, second);
   if(60 < minute || minute < -60 || 60 < second || -second < -60)
   {
       hour_ = 0;
       minute_ = 0;
       second_ = 0;
   }

   // convert everything to second
   // find hour value by dividing total second by 3600
   // find minute value by modding total second by 3600 then dividing result by 60 
   // find second by taking result and mod it by 60
   else
   {
        long result = round((hour * 3600) + (minute * 60) + second);
	    hour_ = result / 3600;
	    result = result % 3600;
	    minute_ = result / 60;
	    result = result % 60;
	    second_ = result;
   }
}

// constructor to take two parameters 
// for the case that there is no hour value given
TimeSpan::TimeSpan(double minute, double second)
{
    //setTimeDouble(0, minute, second);
    if(60 < minute || minute < -60 || 60 < second || second < -60)
    {
        hour_ = 0;
        minute_ = 0;
        second_ = 0;
    }
    else 
    {
        hour_ = 0;
        long result = round((minute * 60) + second);
        result = result % 3600;
        minute_ = result / 60;
        result = result % 60;
        second_ = result;
    }
}

// constructor to take one parameters 
// for the case that there are no hour and no minute values given
TimeSpan::TimeSpan(double second)
{
    //setTimeDouble(0, 0, second);
    if(60 < second || second < -60)
    {
        hour_ = 0;
        minute_ = 0;
        second_ = 0;
    }
    else 
    {
        hour_ = 0;
        minute_ = 0;
        long result = round(second);
        result = result % 3600;
        result = result % 60;
        second_ = result;
    }
}

// hour component
int TimeSpan::getHour() const 
{ 
    return hour_; 
}

// minute component
int TimeSpan::getMinute() const { 
    return minute_; 
}

// second component
int TimeSpan::getSecond() const { 
    return second_; 
}

// set a new time if min and second vals are in the given range
bool TimeSpan::setTime(int hour, int minute, int second)
{
    if(60 < minute || minute < -60 || 60 < second || second < -60)
    {
        return false;
    }
    else
    {
        hour_ = hour;
        minute_ = (60 + minute) % 60;
        second_ = (second + 60) % 60;
    }
    return true;
}

// true if timespan is 0 or larger
bool TimeSpan::isPositive() const 
{ 
    TimeSpan result(0,0,0);
    if(this->getSecond() > result.second_ || this->getSecond() == result.second_)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

// add operator to add given timespans together    
TimeSpan TimeSpan::operator+(const TimeSpan &ts) const {

    TimeSpan result = *this;
	result += ts;
	return result;
}

// operator += to add the righ-hand-side timespan to the left one
TimeSpan TimeSpan::operator+=(const TimeSpan &ts)
{
    hour_ = hour_ + ts.getHour();
    minute_ = minute_ + ts.getMinute();
    second_ = second_ + ts.getSecond();
    return *this;
}

// subtract operator to subtract given timespans from each other
TimeSpan TimeSpan::operator-(const TimeSpan &ts) const {
  TimeSpan result = *this;
  result -= ts;
  return result;
}

// operator -= to subtract the righ-hand-side timespan from the left one
TimeSpan TimeSpan::operator-=(const TimeSpan &ts)
{
    hour_ = hour_ - ts.getHour();
    minute_ = minute_ - ts.getMinute();
    second_ = second_ - ts.getSecond();
    return *this;
}

// multiplication operator to multiply given timespan with an integer
TimeSpan TimeSpan::operator*(unsigned int number) const 
{
    TimeSpan result(0, 0, 0);
    result.hour_ = this->getHour();
    result.minute_ = this->getMinute();
    result.second_ = this->getSecond();
    result.hour_ = result.hour_ * number;
    result.minute_ = result.minute_ * number;
    result.second_ = result.second_ * number;
    return result;
}

// equality ==
// return true if the two given timespans are equal to each other
bool TimeSpan::operator==(const TimeSpan &ts) const 
{ 
    if(hour_ == ts.getHour() && minute_ == ts.getMinute() &&
        second_ == ts.getSecond())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// inequality != 
// return true if the two given timespans are not equal to each other 
bool TimeSpan::operator!=(const TimeSpan &ts) const 
{ 
    if(*this == ts)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// comparison (< operator)
// return true if the left timespan is less than the right one
bool TimeSpan::operator<(const TimeSpan &ts) const 
{
    if(this->hour_ < ts.getHour()) 
    {
        if(this->minute_ < ts.getMinute())
        {
            if(this->second_ < ts.getSecond())
            {
                return true;
            }
        }
    } 
    return false;
}

// comparison (<= operator)
// return true if the left timespan is less than or equal to the right one
bool TimeSpan::operator<=(const TimeSpan &ts) const
{
    if(this->hour_ < ts.getHour() || this->hour_ == ts.getHour())
    {
        if(this->minute_ < ts.getMinute() || this->minute_ == ts.getMinute())
        {
            if(this->second_ < ts.getSecond() || this->second_ == ts.getSecond())
            {
                return true;
            }

        }
    }
    return false;
}

// comparison (> operator)
// return true if the left timespan is greater than the right one
bool TimeSpan::operator>(const TimeSpan &ts) const 
{
    if(this->hour_ > ts.getHour()) 
    {
        if(this->minute_ > ts.getMinute())
        {
            if(this->second_ > ts.getSecond())
            {
                return true;
            }
        }
    } 
    return false;
}

// comparison (>= operator)
// return true if the left timespan is greater than or equal to the right one
bool TimeSpan::operator>=(const TimeSpan &ts) const
{
    if(this->hour_ > ts.getHour() || this->hour_ == ts.getHour())
    {
        if(this->minute_ > ts.getMinute() || this->minute_ == ts.getMinute())
        {
            if(this->second_ > ts.getSecond() || this->second_ == ts.getSecond())
            {
                return true;
            }
        }
    }
    return false;
}

