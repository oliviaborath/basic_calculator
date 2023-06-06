#ifndef TIMESPAN_H
#define TIMESPAN_H

#include <iostream>
using namespace std;

class TimeSpan {
  // print out the timespan in hr:min:second format
  // handle the leading zeros
  friend ostream &operator<<(ostream &out, const TimeSpan &ts);

public:
  // explicit TimeSpan(int Hour = 0, int Minute = 0, int Second = 0);
  // constructor to take three parameters 
  explicit TimeSpan(double hour = 0, double minute = 0, double second = 0);

  // constructor to take two parameters 
  // for the case that there is no hour value given
  explicit TimeSpan(double minute = 0, double second = 0);

  // constructor to take one parameters 
  // for the case that there are no hour and no minute values given
  explicit TimeSpan(double second = 0);

  // add operator to add given timespans together     
  TimeSpan operator+(const TimeSpan &ts) const;

  // subtract operator to subtract given timespans from each other
  TimeSpan operator-(const TimeSpan &ts) const;

  // check equality
  // return true if the two given timespans are equal to each other
  bool operator==(const TimeSpan &ts) const;

  // check if not equal
  // return true if the two given timespans are not equal to each other 
  bool operator!=(const TimeSpan &ts) const;

  // multiply timespan by an unsigned number
  TimeSpan operator*(unsigned int number) const;
  
  // operator += to add the righ-hand-side timespan to the left one
  TimeSpan operator+=(const TimeSpan &ts);

  // operator -= to subtract the righ-hand-side timespan from the left one
  TimeSpan operator-=(const TimeSpan &ts);

  // comparison (< operator)
  // return true if the left timespan is less than the right one
  bool operator<(const TimeSpan &ts) const;

  // comparison (<= operator)
  // return true if the left timespan is less than or equal to the right one
  bool operator<=(const TimeSpan &ts) const;

  // comparison (> operator)
  // return true if the left timespan is greater than the right one
  bool operator>(const TimeSpan &ts) const;

  // comparison (>= operator)
  // return true if the left timespan is greater than or equal to the right one
  bool operator>=(const TimeSpan &ts) const;

  // hour component of timespan
  int getHour() const;

  // minute component of timespan
  int getMinute() const;

  // second component of timespan
  int getSecond() const;

  // set time component of timespan with integer
  // set a new time if min and second vals are in the given range
  bool setTime(int hour, int minute, int second);

  // true if timespan is 0 or larger
  bool isPositive() const;

private:
    int hour_;
    int minute_;
    int second_;
};

#endif 