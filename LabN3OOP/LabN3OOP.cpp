#include <iostream>
#include <list>

class Point2D {
protected:
	double x, y;
public:
	Point2D() {
		x = 0;
		y = 0;
		printf("Point2D()");
	}
	Point2D(double x, double y) {
		this->x = x;
		this->y = y;
		printf("Point2D(double x, double y)");
	}
	Point2D(const Point2D& point) {
		x = point.x;
		y = point.y;
		printf("Point2D(const Point2D &point)");
	}
	~Point2D() {
		printf("~Point2D()");
	}
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
	void setX(double x) {
		this->x = x;
	}
	void SetY(double y) {
		this->y = y;
	}
};

int main()
{

	return 0;
}