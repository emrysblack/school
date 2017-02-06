/*****************************************
 * POINT
 * A very simple point class.  You will most
 * likely want to use something more better
 * than this
 ****************************************/
#ifndef _POINT_H
#define _POINT_H

/*******************
 * POINT
 *******************/
class Point
{
public:
   // constructors
   Point() : x(0.0), y(0.0) {};
   Point(const Point &pt) : x(pt.x), y(pt.y) {};
   Point(bool noError) : x(0.0), y(0.0) {};

   // getters
   float getX()    const { return x;     };
   float getY()    const { return y;     };
   float getXMax() const { return  100;  };
   float getYMax() const { return  100;  };
   float getXMin() const { return -100;  };
   float getYMin() const { return -100;  };

   // setters
   void setX(float x)    { this->x = x;  };
   void setY(float y)    { this->y = y;  };
   void addX(float dx)   { this->x += dx; };
   void addY(float dy)   { this->y += dy; };

private:
   float x;
   float y;
};

#endif 
