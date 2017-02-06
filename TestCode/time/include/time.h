// header file for ercanbrack time class
#ifndef TIME_H
#define TIME_H

/*****************************************************************************
 * Class Name: Time
 * Summary: This class contains methods for the the creation,
 *          manipulation, input, and output of time objects
 *****************************************************************************/
class Time
{
   public:

      Time(int theHour, int theMin, int theSec);
      Time(int theHour, int theMin);
      Time(void);
      void setMinute(int theMinute);
      void setHour(int theHour);
      void setSecond(int theSecond);
      void addSeconds(int seconds2Add);
      void addMinutes(int minutes2Add);
      // add hours and returns # of days of overflow
      int  addHours(int hours2Add);
      // display as military time - default no seconds (hh:mm)
      void displayMilitaryTime(bool displaySeconds = false);
      // display the prompt and read data into the time object
      void promptForTime(std::string prompt, bool readSeconds = false);
      // add two time objects & return the resulting time object
      Time operator + (const Time time1);                           

      // logical operators
      bool operator < (const Time &time1);
      bool operator > (const Time &time1);
      bool operator == (const Time &time1);
      bool operator <= (const Time &time1);
      bool operator >= (const Time &time1);

      // displays the time object in the format "hh:mm"
      friend std::ostream& operator << (std::ostream &out, const Time &time1);
      // reads into the time object.  Expects format "hh:mm"
      friend std::istream& operator >> (std::istream &in, Time &time1);

   private:
      int hour;
      int minute;
      int second;
};
#endif
