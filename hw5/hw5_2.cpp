#include<iostream>
#include<vector>
using namespace std;
const double pi = 3.14159;

class Shape {
	double area;
	double volume;
public:
	virtual double getArea();
	virtual double getVolume();
};

class TwoDimensionalShape :public Shape {
	double area;
public:
	virtual double getArea();
};

class ThreeDimensionalShape :public Shape {
	double area;
	double volume;
public:
	virtual double getArea();
	virtual double getVolume();
};

class Circle :public TwoDimensionalShape {
	double r;//the radius
public:
	Circle(double r);//initialize Circle
	virtual double getArea();//calculate the area of Circle
};

class Square :public TwoDimensionalShape {
	double a;//the length of side
public:
	Square(double a);//initialize Square
	virtual double getArea();//calculate the area of Square
};

class Ball :public ThreeDimensionalShape {
	double r;//the radius
public:
	Ball(double r);//initialize Ball
	virtual double getArea();//calculate the area of Ball
	virtual double getVolume();//calculate the volume of Ball
};

class Cylinder :public ThreeDimensionalShape {
	double r, h;//the radius and height
public:
	Cylinder(double r, double h);//initialize Cylinder
	virtual double getArea();//calculate the area of Cylinder 
	virtual double getVolume();//calculate the volume of Cylinder
};
double Shape::getArea() {
	return area;
}
double Shape::getVolume() {
	return volume;
}

double TwoDimensionalShape::getArea() {
	return area;
}

double ThreeDimensionalShape::getArea() {
	return area;
}

double ThreeDimensionalShape::getVolume() {
	return volume;
}


Circle::Circle(double R)
	:r(R) {};
double Circle::getArea() {
	return pi*r*r;
}

Square::Square(double A)
	:a(A) {};
double Square::getArea() {
	return a*a;
}

Ball::Ball(double R)
	:r(R) {};
double Ball::getArea() {
	return 4 * pi*r*r;
}
double Ball::getVolume() {
	return 4 * pi*r*r*r / 3;
}

Cylinder::Cylinder(double R, double H)
	:r(R), h(H) {};
double Cylinder::getArea() {
	return 2 * pi*r*r + 2 * pi*r*h;
}
double Cylinder::getVolume() {
	return pi*r*r*h;
}
void print(Shape* shapeX) {//cout the area and volume of shape
	if (dynamic_cast<TwoDimensionalShape*>(shapeX)) {//if this shape is 2D
		cout << "the area is:" << shapeX->getArea() << endl;
	}
	if (dynamic_cast<ThreeDimensionalShape*>(shapeX)) {//if this shape is 3D
		cout << "the area is:" << shapeX->getArea() << endl;
		cout << "the volume is:" << shapeX->getVolume() << endl;
	}
}



int main()
{
	Circle circle(1.0);
	Square square(2.0);
	Ball ball(3.0);
	Cylinder cylinder(4.0, 5.0);//initialize
	vector<Shape*>shapes;
	shapes.push_back(&circle);
	shapes.push_back(&square);
	shapes.push_back(&ball);
	shapes.push_back(&cylinder);//get shapes
	for (int i = 0; i < shapes.size();i++)
		print(shapes[i]);
    return 0;
}

