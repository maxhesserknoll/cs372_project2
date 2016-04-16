#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <fstream>
#include <initializer_list>
#include <math.h>

#define PI 3.141592653589793238

using std::string;

class AbstractShape 
{
public:
	virtual string toString(double xC, double yC)
	{
		string pString = "";
		pString += "gsave";
		pString += '\n';
		pString += std::to_string(xC) + " " + std::to_string(yC) + " translate" + '\n';
		for (auto i : psCode) {
			pString += i + '\n';
		}
		pString += "grestore";
		pString += '\n';
		return pString;
	}
	std::deque<string> psCode;
	double boundingWidth, boundingHeight; //boundingbox
	virtual ~AbstractShape() {};
};

class Circle : public AbstractShape
{
public:
	Circle() = delete;
	virtual ~Circle() {};
	Circle(double radius)
	{
		if (radius < 0)
		{
			throw;
		}
		psCode.push_back(std::to_string(radius));
		psCode.push_back("/radius 1 index def");
		psCode.push_back("newpath");
		psCode.push_back("0 0 radius 0 360 arc stroke");
		boundingWidth = 2 * radius;
		boundingHeight = 2 * radius;
	}
};

class Polygon : public AbstractShape
{
public:
	Polygon() = delete;
	virtual ~Polygon() {};
	Polygon(int numSides, double sideLength)
	{
		if (numSides < 0 || sideLength < 0)
		{
			throw;
		}
		std::vector<std::pair<double, double>> points;
		for (int i = 0; i < numSides;i++) {
			double x = (sideLength / 2) * (sin(((2 * i + 1)*PI) / numSides) / (sin(PI / numSides)));
			double y = (-sideLength / 2) * (cos(((2 * i + 1)*PI) / numSides) / (sin(PI / numSides)));
			points.push_back(std::pair<double, double>(x, y));
		}

		if (numSides % 2 != 0) //check for odd
		{
			boundingWidth = sideLength*(sin((PI*(numSides - 1)) / (2 * numSides)) / sin(PI / numSides));
			boundingHeight = sideLength*((1 + cos(PI / numSides)) / (2 * sin(PI / numSides)));
		}
		if (numSides % 2 == 0 && numSides % 4 != 0) //even but not divisible by 4
		{
			boundingWidth = sideLength*(1 / sin(PI / numSides));
			boundingHeight = sideLength*(cos(PI/numSides)/sin(PI/numSides));
		}
		if (numSides % 4 == 0) //divisible by 4
		{
			boundingWidth = sideLength*(cos(PI/numSides)/sin(PI/numSides));
			boundingHeight = sideLength*(cos(PI / numSides) / sin(PI / numSides));
		}

		psCode.push_back("newpath");
		psCode.push_back("0 0 moveto");
		psCode.push_back(std::to_string(points[0].first) + " " + std::to_string(points[0].second) + " moveto");
		for (int j = 1; j < numSides;++j)
		{
			psCode.push_back(std::to_string(points[j].first) + " " + std::to_string(points[j].second) + " lineto");
		}
		psCode.push_back("closepath");
		psCode.push_back("stroke");
	}
};

class Rectangle : public AbstractShape
{
public:
	Rectangle() = delete;
	virtual ~Rectangle() {};
	Rectangle(double width, double height)
	{
		if (width < 0 || height < 0)
		{
			throw;
		}
		psCode.push_back("newpath");
		psCode.push_back(std::to_string(-(width / 2)) + " " + std::to_string(-(height / 2)) + " moveto");
		psCode.push_back("0 " + std::to_string(height) + " rlineto");
		psCode.push_back(std::to_string(width) + " 0 rlineto");
		psCode.push_back("0 " + std::to_string(-height) + " rlineto");
		psCode.push_back("closepath stroke");
		boundingHeight = height;
		boundingWidth = width;
	}
};

class Spacer : public AbstractShape
{
public:
	Spacer() = delete;
	virtual ~Spacer() {};
	Spacer(double width, double height)
	{
		if (width < 0 || height < 0)
		{
			throw;
		}
		boundingHeight = height;
		boundingWidth = width;
	}

private:
	string toString(double xC, double yC)
	{
		return "";
	}
};

class Square : public AbstractShape
{
public:
	Square() = delete;
	virtual ~Square() {};
	Square(double sideLength)
	{
		if (sideLength < 0)
		{
			throw;
		}
		Polygon tempSquare(4, sideLength);
		psCode = tempSquare.psCode;
		boundingHeight = tempSquare.boundingHeight;
		boundingWidth = tempSquare.boundingWidth;
	}
};

class Triangle : public AbstractShape
{
public:
	Triangle() = delete;
	virtual ~Triangle() {};
	Triangle(double sideLength)
	{
		if (sideLength < 0)
		{
			throw;
		}
		Polygon tempTriangle(3, sideLength);
		psCode = tempTriangle.psCode;
		boundingHeight = tempTriangle.boundingHeight;
		boundingWidth = tempTriangle.boundingWidth;
	}
};

class Trapezoid : public AbstractShape
{
public:
    Trapezoid() = delete;
    virtual ~Trapezoid() {};
    Trapezoid(double topLength, double bottomLength, double height)
    {
        if (topLength < 0 || bottomLength < 0 || height < 0)
        {
            throw;
        }
        
        boundingHeight = height;
        (topLength > bottomLength)? boundingWidth = topLength : boundingWidth = bottomLength ;
        
        psCode.push_back(std::to_string(topLength) + " " + std::to_string(bottomLength) + " " + std::to_string(height));
        psCode.push_back("/topside 1 index def");
        psCode.push_back("/bottomside 2 index def");
        psCode.push_back("/hieght 3 index def");
        psCode.push_back("newpath");
        psCode.push_back("0 0 moveto");
        psCode.push_back("bottomside 2  div");
        psCode.push_back("hieght -2 div");
        psCode.push_back("moveto");
        psCode.push_back("bottomside -2 div");
        psCode.push_back("hieght -2 div");
        psCode.push_back("lineto");
        psCode.push_back("topside -2 div");
        psCode.push_back("hieght 2 div");
        psCode.push_back("lineto");
        psCode.push_back("topside 2 div");
        psCode.push_back("hieght 2 div");
        psCode.push_back("lineto");
        psCode.push_back("closepath");
        psCode.push_back("stroke");
    }
};


class FiftyShades : public AbstractShape
{
public:
    FiftyShades() = delete;
    virtual ~FiftyShades() {};
    FiftyShades(double sideLength)
    {
        if (sideLength < 0)
        {
            throw;
        }
        
        boundingHeight = sideLength;
        boundingWidth = sideLength;
        
        psCode.push_back(std::to_string(sideLength));
        psCode.push_back("/size 1 index def");
        psCode.push_back("/50size size 50 div def");
        psCode.push_back("size -2 div size -2 div translate");
        psCode.push_back("newpath");
        psCode.push_back("0 0 moveto");
        psCode.push_back("50 -1 0{");
        psCode.push_back("0 0 moveto");
        psCode.push_back("dup");
        psCode.push_back("dup");
        psCode.push_back(".02 mul");
        psCode.push_back("setgray");
        psCode.push_back("dup");
        psCode.push_back("50size mul");
        psCode.push_back("0 lineto");
        psCode.push_back("50size mul");
        psCode.push_back("size lineto");
        psCode.push_back("0 size lineto");
        psCode.push_back("closepath");
        psCode.push_back("fill");
        psCode.push_back("stroke");
        psCode.push_back("}for");
        psCode.push_back("0 0 moveto");
        psCode.push_back("0 size lineto");
        psCode.push_back("size size lineto");
        psCode.push_back("size 0 lineto");
        psCode.push_back("closepath");
        psCode.push_back("stroke");
        
    }
};

class ShapeDecorator : public AbstractShape 
{
public:
	AbstractShape* theShape;
	virtual ~ShapeDecorator() {};
};

class Rotate : public ShapeDecorator
{
public:
	Rotate() = delete;
	virtual ~Rotate() {};
	Rotate(AbstractShape *shape, int angle) 
	{
		if (angle % 90 != 0)
        {
			throw;
		}
		theShape = shape;
		psCode = theShape->psCode;

		psCode.push_front(std::to_string(angle) + " rotate");

		if ((angle/90) % 2 != 0) 
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
};

class Scaled : public ShapeDecorator
{
public:
	Scaled() = delete;
	virtual ~Scaled() {};
	Scaled(AbstractShape *shape, double sx, double sy)  {
		theShape = shape;
		psCode = theShape->psCode;
		psCode.push_front(std::to_string(sx) + " " + std::to_string(sy) + " scale");
		boundingWidth = shape->boundingWidth * fabs(sx);
		boundingHeight = shape->boundingHeight * fabs(sy);
		psCode.push_front("gsave");
		psCode.push_back("grestore");
	}

};

class Layered : public ShapeDecorator
{
public:
	Layered() = delete;
	virtual ~Layered() {};
	Layered(std::initializer_list<AbstractShape *> x)
	{
		double maxWidth = 0;
		double maxHeight = 0;
		for (auto i : x) {
			if (i->boundingHeight > maxHeight)
			{
				maxHeight = i->boundingHeight;
			}
			if (i->boundingWidth > maxWidth)
			{
				maxWidth = i->boundingWidth;
			}
			for (auto j : i->psCode)
			{
				psCode.push_back(j);
			}
		}
		boundingHeight = maxHeight;
		boundingWidth = maxWidth;
	}
};

class Vertical : public ShapeDecorator
{
public:
	Vertical() = delete;
	virtual ~Vertical() {};
	Vertical(std::initializer_list<AbstractShape *> x) : shapeVector(x)
	{
		double newShapeCenter = 0;
		double maxHeight = (*shapeVector.begin())->boundingHeight;
		double maxWidth = (*shapeVector.begin())->boundingWidth;
		psCode = (*shapeVector.begin())->psCode;
		for (auto i = shapeVector.begin() + 1; i != shapeVector.end(); ++i) 
		{

			if ((*i)->boundingWidth > maxWidth)
			{
				maxWidth = (*i)->boundingWidth;
			}
			maxHeight += (*i)->boundingHeight;
			newShapeCenter += (*(i - 1))->boundingHeight / 2 + (*i)->boundingHeight / 2;
			psCode.push_back("gsave");
			psCode.push_back("0 " + std::to_string(newShapeCenter) + " translate");
			for (auto j : (*i)->psCode) {
				psCode.push_back(j);
			}
			psCode.push_back("grestore");

		}
		boundingHeight = maxHeight;
		boundingWidth = maxWidth;
	}
private:
	std::vector <AbstractShape *> shapeVector;
};

class Horizontal : public ShapeDecorator
{
public:
	Horizontal() = delete;
	virtual ~Horizontal() {};
	Horizontal(std::initializer_list<AbstractShape *> x) : shapeVector(x) {
		double newShapeCenter = 0;
		double maxHeight = (*shapeVector.begin())->boundingHeight;
		double maxWidth = (*shapeVector.begin())->boundingWidth;
		psCode = (*shapeVector.begin())->psCode;
		for (auto i = shapeVector.begin() + 1; i != shapeVector.end(); ++i)
		{

			if ((*i)->boundingHeight > maxHeight)
			{
				maxHeight = (*i)->boundingHeight;
			}
			maxWidth += (*i)->boundingWidth;

			newShapeCenter += (*(i - 1))->boundingWidth / 2 + (*i)->boundingWidth / 2;
			psCode.push_back("gsave");
			psCode.push_back(std::to_string(newShapeCenter) + " 0 translate");
			for (auto j : (*i)->psCode) {
				psCode.push_back(j);
			}
			psCode.push_back("grestore");

		}
		boundingHeight = maxHeight;
		boundingWidth = maxWidth;
	}
private:
	std::vector<AbstractShape *> shapeVector;

};