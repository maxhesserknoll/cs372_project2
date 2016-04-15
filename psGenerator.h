#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <fstream>
#include <initializer_list>

using std::string;
using RotationAngle = int;

class AbstractShape 
{
public:
	virtual string toString(double  xC, double yC)=0;
	std::deque<string> psCode;
	double boundingWidth, boundingHeight; //boundingbox
	double centerX, centerY; //center of shape
};

class Circle : public AbstractShape
{
public:

	Circle(double radius)
	{
		psCode.push_back(std::to_string(radius));
		psCode.push_back("/radius 1 index def");
		psCode.push_back("newpath");
		psCode.push_back("0 0 radius 0 360 arc stroke");
		boundingWidth = 2 * radius;
		boundingHeight = 2 * radius;
		centerX = 0;
		centerY = 0;
	}

	string toString(double xC, double yC)
	{
		string pString = "";
		pString += std::to_string(xC) + " " + std::to_string(yC) + " translate" + '\n';
		for (auto i : psCode) {
			pString += i + '\n';
		}
		return pString;
	}

private:
	Circle() {};
};

class Polygon : public AbstractShape
{
public:

	Polygon(int numSides, double sideLength)
	{

	}

	string toString(double xC, double yC)
	{

	}

private:
	Polygon() {};
};

class Rectangle : public AbstractShape
{
public:
	
	Rectangle(double width, double height)
	{

	}

	string toString(double xC, double yC)
	{

	}

private:
	Rectangle() {};
};

class Spacer : public AbstractShape
{
public:

	Spacer(double width, double height)
	{

	}

	string toString(double xC, double yC)
	{

	}

private:
	Spacer() {};
};

class Square : public AbstractShape
{
public:

	Square(double sideLength)
	{

	}

	string toString(double xC, double yC)
	{

	}

private:
	Square() {};
};

class Triangle : public AbstractShape
{
public:

	Triangle(double sideLength)
	{

	}

	string toString(double xC, double yC)
	{

	}

private:
	Triangle() {};
};

class ShapeDecorator : public AbstractShape 
{
public:
	//ShapeDecorator(AbstractShape *shape) : theShape(shape) {};
	AbstractShape* theShape;
};

class Rotate : public ShapeDecorator
{
public:
	Rotate(AbstractShape *shape, RotationAngle angle) 
	{
		theShape = shape;
		psCode = theShape->psCode;

		psCode.push_front(std::to_string(angle * 90) + " rotate");

		centerX = shape->centerX;
		centerY = shape->centerY;
		if (angle % 2 != 0) 
		{
			boundingWidth = shape->boundingHeight;
			boundingHeight = shape->boundingWidth;
		}
		else 
		{
			boundingWidth = shape->boundingWidth;
			boundingHeight = shape->boundingHeight;
		}
	}
	string toString(double xC, double yC)
	{
		string pString = "";
		pString += std::to_string(xC) + " " + std::to_string(yC) + " translate" + '\n';
		for (auto i : psCode) {
			pString += i + '\n';
		}
		return pString;
	}
};

class Scaled : public ShapeDecorator
{
public:
	Scaled(AbstractShape *shape, double sx, double sy)  {
		theShape = shape;
		psCode = theShape->psCode;
		psCode.push_front(std::to_string(sx) + " " + std::to_string(sy) + " scale");
		boundingWidth = shape->boundingWidth * sx;
		boundingHeight = shape->boundingHeight * sy;
		centerX = shape->centerX;
		centerY = shape->centerY;
	}

	string toString(double xC, double yC)
	{
		string pString = "";
		pString += std::to_string(xC) + " " + std::to_string(yC) + " translate" + '\n';
		for (auto i : psCode) {
			pString += i + '\n';
		}
		return pString;
	}
};

class Layered : public ShapeDecorator
{
public:

	Layered(std::initializer_list<AbstractShape> x)
	{

	}

	string toString(double xC, double yC)
	{

	}

private:
	Layered() {};
};

class Vertical : public ShapeDecorator
{
public:

	Vertical(std::initializer_list<AbstractShape> x)
	{

	}

	string toString(double xC, double yC)
	{

	}

private:
	Vertical() {};

};

class Horizontal : public ShapeDecorator
{
public:

	Horizontal(std::initializer_list<AbstractShape> x) {

	}

	string toString(double xC, double yC)
	{

	}

private:
	Horizontal() {};

};