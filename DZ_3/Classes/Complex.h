#pragma once
#include <iostream>
#include <cmath>

class Complex
{
public:
	Complex(double re = 0, double im = 0)
	{
		Re = re;
		Im = im;
	}
	double Re;
	double Im;
	
	inline friend std::ostream& operator<< (std::ostream& o, const Complex& c)
	{
		return o << '(' << c.Re << ", " << c.Im << ')' << std::endl;
	}

	inline Complex operator+ (const Complex& c) const
	{
		return Complex(Re + c.Re, Im + c.Im);
	}

	inline Complex operator- (const Complex& c) const
	{
		return Complex(Re - c.Re, Im - c.Im);
	}

	inline Complex operator* (const Complex& c) const
	{
		//(x1 + i * y1)* (x2 + i * y2) = (x1 * x2 – y1 * y2, i * (x1 * y2 + x2 * y1))
		return Complex(Re * c.Re - Im * c.Im, Re * c.Im + c.Re * Im);
	}

	inline Complex operator/ (const Complex& c) const
	{
		//(x1+i*y1)/(x2+i*y2) = 
		//((x1 * x2 + y1 * y2) / (x2 * x2 + y2 * y2), i * (-x1 * y2 + x2 * y1) / (x2 * x2 + y2 * y2))
		return Complex((Re * c.Re + Im * c.Im) / (c.Re * c.Re + c.Im * c.Im), (-Re * c.Im + c.Re * Im) / (c.Re * c.Re + c.Im * c.Im));
	}

	inline Complex Conjugate() const
	{
		return Complex(Re, -Im);
	}

	inline double Mod() const
	{
		return sqrt(Re * Re + Im * Im);
	}

	inline double Arg() const
	{
		if (Mod() == 0)
			return 0;

		if (Re > 0)
			return atan(Im / Re);
		
		if (Re < 0)
			if (Im >= 0)
				return acos(-1) + atan(Im / Re);
			else
				return -acos(-1) - atan(Im / Re);
		else
			if (Im > 0)
				return acos(0);
			else
				return -acos(0);
	}
};

