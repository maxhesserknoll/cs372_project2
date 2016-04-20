// psGenerator.h
// CS 372
// Project 2
// Group 1
// 20 April 2016

// There is no associated source file.

// PostScript Generator Library:
// C++ library that takes commands to draw certain shapes
// and outputs code in the PostScript programming language.
// Uses Decorator design pattern.


#include <vector>
#include <string>
#include <deque> //used to store the pscode
#include <initializer_list> //to pass multiple shapes to a function
#include <math.h> //for sin and cos functions
#define PI 3.141592653589793238

using std::string;

// *********************************************************************
// class AbstractShape - Class Declaration
// *********************************************************************

// class AbstractShape
// AbstractShape Class which all shape and decorators will be based on
// via the decorator design pattern.
class AbstractShape 
{
public:
    //storage for postscript code
	std::deque<string> psCode;
    
	double boundingWidth, boundingHeight; //boundingbox
    
	//virtual destructor
	virtual ~AbstractShape() = default;
    
	//tostring function that will output the deque and put it into one string.
	virtual string toString(double xC, double yC)
	{
		string psString = "";
		psString += "gsave";
		psString += '\n';
		psString += std::to_string(xC) + " " + std::to_string(yC) + " translate" + '\n';
		for (auto i : psCode) {
			psString += i + '\n';
		}
		psString += "grestore";
		psString += '\n';
		return psString;
	}
};

// *********************************************************************
// class Circle - Class Declaration
// *********************************************************************

// class Circle, inherits from AbstractShape
// Class that takes a parameter of a double and generates a circle with the associated value.
// default constructor is deleted
//throws if radius is less than 0
class Circle : public AbstractShape
{
public:

	//default ctor
	Circle() = delete;
	//virtual destructor
	virtual ~Circle() {};
	
	//ctor with one parameter
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

// *********************************************************************
// class Polygon - Class Declaration
// *********************************************************************

// class Polygon, inherits from AbstractShape
// Class that generates a polygon with the associated numsides and sideLength
//throws if numSides <2 or sideLength is less than 0
class Polygon : public AbstractShape
{
public:

	//default ctor
	Polygon() = delete;
	
	//virtual dctor
	virtual ~Polygon() {};
	
	//ctor of two parameters
	Polygon(int numSides, double sideLength)
	{
		if (numSides < 2 || sideLength < 0)
		{
			throw;
		}
		//storage and calculation of the associated points
		std::vector<std::pair<double, double>> points;
		for (int i = 0; i < numSides;i++) {
			double x = (sideLength / 2) * (sin(((2 * i + 1)*PI) / numSides) / (sin(PI / numSides)));
			double y = (-sideLength / 2) * (cos(((2 * i + 1)*PI) / numSides) / (sin(PI / numSides)));
			points.push_back(std::pair<double, double>(x, y));
		}

		//bounding box calculation
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

		//postscript generation
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

// *********************************************************************
// class Rectangle - Class Declaration
// *********************************************************************

// class Rectangle, inherits from AbstractShape
// Class that constructs a rectangle with the associated width and height
//throws if width or height is below 0
class Rectangle : public AbstractShape
{
public:

	//default ctor
	Rectangle() = delete;
	
	//virtual dctor
	virtual ~Rectangle() {};
	
	//ctor with two parameters
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

// *********************************************************************
// class Spacer - Class Declaration
// *********************************************************************

// class Spacer, inherits from AbstractShape
// Class that generates a bounding box based on given width and height
//does not draw anything

class Spacer : public AbstractShape
{
public:

	//default ctor
	Spacer() = delete;
	
	//virtual dctor
	virtual ~Spacer() {};
	
	//ctor of two parameters
	Spacer(double width, double height)
	{
		if (width < 0 || height < 0)
		{
			throw;
		}
		boundingHeight = height;
		boundingWidth = width;
	}

	//overloaded tostring
	string toString(double xC, double yC)
	{
		return "";
	}
};

// *********************************************************************
// class Square - Class Declaration
// *********************************************************************

// class Square, inherits from AbstractShape
// Class constructs a square by taking parameter sideLength and passing it
// to polygon.
//throws if sideLength is less than 0
class Square : public AbstractShape
{
public:

	//default ctor
	Square() = delete;

	//virtual dctor
	virtual ~Square() {};
	
	//ctor with one parameter
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

// *********************************************************************
// class Triangle - Class Declaration
// *********************************************************************

// class Triangle, inherits from AbstractShape
// Class that constructs an equilateral triangle in postscript based on sideLength.
// Passes sidelength to Polygon.
// throws when sideLength is less than 0
class Triangle : public AbstractShape
{
public:

	//default ctor
	Triangle() = delete;
	
	//virtual dctor
	virtual ~Triangle() {};
	
	//ctor with one parameter
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

// *********************************************************************
// class Trapezoid - Class Declaration
// *********************************************************************

// class Trapezoid, inherits from AbstractShape
// Class that takes the topLength, bottomLength, and height and generates
// a trapezoid based on those parameters.
//throws when toplength, bottomlength, and height are less than 0
class Trapezoid : public AbstractShape
{
public:

	//default ctor
    Trapezoid() = delete;
	
	//virtual dctor
    virtual ~Trapezoid() {};
    
	//ctor with three parameters
	Trapezoid(double topLength, double bottomLength, double height)
    {
        if (topLength < 0 || bottomLength < 0 || height < 0)
        {
            throw;
        }
        
        boundingHeight = height;
        (topLength > bottomLength)? boundingWidth = topLength : boundingWidth = bottomLength ;
        
        psCode.push_back(std::to_string(height) + " " + std::to_string(bottomLength) + " " + std::to_string(topLength));
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


// *********************************************************************
// class FiftyShades - Class Declaration
// *********************************************************************

// class FiftyShades, inherits from AbstractShape
// Class that generates a square with 50 shades of gray
// takes sideLength parameter and generates accordingly.
// throws when sideLength is less than 0
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
        
        psCode.push_back("gsave");
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
        psCode.push_back("grestore");
        
    }
};

// *********************************************************************
// class ShapeDecorator - Class Declaration
// *********************************************************************

// class ShapeDecorator, inherits from AbstractShape
// Base class for decorator
class ShapeDecorator : public AbstractShape 
{
public:
	AbstractShape* theShape;
	virtual ~ShapeDecorator() {};
};

// *********************************************************************
// class Rotate - Class Declaration
// *********************************************************************

// class Rotate, inherits from ShapeDecorator
// Class that constructs a new shape of the given shape but rotated by the given angle.
// throws if angle is not divisible by 90 degrees.
class Rotate : public ShapeDecorator
{
public:

	//default ctor
	Rotate() = delete;
	
	//virtual dctor
	virtual ~Rotate() {};
	
	//ctor of two parameters
	Rotate(AbstractShape *shape, int angle) 
	{
		if ((angle % 90) != 0)
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
        psCode.push_front("gsave");
        psCode.push_back("grestore");
	}
};

// *********************************************************************
// class Scaled - Class Declaration
// *********************************************************************

// class Scaled, inherits from ShapeDecorator
// Class takes shape and constructs a new shape with the associated scaled values
class Scaled : public ShapeDecorator
{
public:
	
	//default ctor
	Scaled() = delete;
	
	//virtual dctor
	virtual ~Scaled() {};
	
	//ctor that takes three parameters
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

// *********************************************************************
// class Layered - Class Declaration
// *********************************************************************

// class Layered, inherits from ShapeDecorator
// Class that takes a variable amount of shapes and layers them on top of each other
// and makes that a new shape out of that.
class Layered : public ShapeDecorator
{
public:
	
	//default ctor
	Layered() = delete;
	
	//virtual dctor
	virtual ~Layered() {};
	
	//ctor that can take multiple parameters via an initalizer list
	Layered(std::initializer_list<AbstractShape *> x)
	{
		double maxWidth = 0;
		double maxHeight = 0;
		
		//for loop that places shapes on top of each other
		//changes the boundingHeight and boundingWidth to largest value of the shapes given
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

// *********************************************************************
// class Vertical - Class Declaration
// *********************************************************************

// class Vertical, inherits from ShapeDecorator
// Class that constructs a new shape by placing the given shapes vertical from each other.
class Vertical : public ShapeDecorator
{
public:

	//default ctor
	Vertical() = delete;
	
	//virtual dctor
	virtual ~Vertical() {};
	
	//ctor that can take multiple parameters via an initalizer list
	Vertical(std::initializer_list<AbstractShape *> x) : shapeVector(x)
	{
		//takes first shape and set its initial boundingBox and boundingWidth
		double newShapeCenter = 0;
		double maxHeight = (*shapeVector.begin())->boundingHeight;
		double maxWidth = (*shapeVector.begin())->boundingWidth;
		psCode = (*shapeVector.begin())->psCode;
		
		//stacks shape based on the boundingheight, and adds to total boundingHeight
		//also checks for max boundingWidth.
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
	//used to convert initalizer list into a vector
	std::vector <AbstractShape *> shapeVector;
};

// *********************************************************************
// class Horizontal - Class Declaration
// *********************************************************************

// class Horizontal, inherits from ShapeDecorator
// Class that generates a new shape by placing the shapes passed to it
// along the horizontal or x axis. 
class Horizontal : public ShapeDecorator
{
public:

	//default ctor
	Horizontal() = delete;
	
	//virtual dctor
	virtual ~Horizontal() {};
	
	//ctor that takes multiple parameters via an initalizer list.
	Horizontal(std::initializer_list<AbstractShape *> x) : shapeVector(x) {
		
		//the first shape is placed
		double newShapeCenter = 0;
		double maxHeight = (*shapeVector.begin())->boundingHeight;
		double maxWidth = (*shapeVector.begin())->boundingWidth;
		psCode = (*shapeVector.begin())->psCode;
		
		//every other shape is placed horizontal to the first shape by its associated boundingWidth
		//the boundingWidth is then added to the total and boundingHeight is the largest boundingHeight of the shapes given.
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
	//used to convert initalizer list into a vector
	std::vector<AbstractShape *> shapeVector;

};