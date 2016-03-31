#ifndef DEF_VECTOR2
#define DEF_VECTOR2

#include <math.h>

class CVector2
{
public:
	double x;
	double y;
	CVector2(){};
	CVector2(double xx, double yy)
	{
		x=xx;
		y=yy;
	}

	inline CVector2& operator += (const CVector2& in)
	{
		x +=in.x;
		y +=in.y;
		return *this;
	};

	inline CVector2& operator -=(const CVector2& in)
	{
		CVector2 out;
		x -= in.x;
		y -= in.y;
		return *this;
	};

	inline CVector2& operator *=(double &in)
	{
		x *=in;
		y *=in;
		return *this;
	};

	inline CVector2& operator /=(double &in)
	{
		x /=in;
		y /=in;
		return *this;
	};

	inline CVector2 operator + (const CVector2& v) const
	{
		return CVector2(x + v.x, y + v.y);
	}

	inline CVector2 operator -(const CVector2& v) const
	{
		return CVector2(x - v.x, y - v.y);
	};

	inline CVector2 operator * (double  in) const
	{
		return CVector2( x*in , y*in);
	};

	inline CVector2 operator /(double in) const
	{
		return CVector2( x/in , y/in);
	};

	inline bool operator == (const CVector2& in)
	{
		if (in.x==x && in.y==y ) return true;
		return false;
	};

	inline double length()
	{
        return sqrt(x*x+y*y);
	}
	
};
#endif
