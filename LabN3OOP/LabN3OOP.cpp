#include <iostream>

using namespace std;

class Point2D {
protected:
	double x, y;
public:
	Point2D() {
		x = 0;
		y = 0;
		printf("Point2D()\n");
	}
	Point2D(double x, double y) {
		this->x = x;
		this->y = y;
		printf("Point2D(double x, double y)\n");
	}
	Point2D(const Point2D& point) {
		this->x = point.x;
		this->y = point.y;
		printf("Point2D(const Point2D &point)\n");
	}
	~Point2D() {
		printf("~Point2D()\n");
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

class Figure2D {	// Хранилище
protected:
	Point2D** arr;	// Массив элементов
	int max;	// Размер массива
public:
	Figure2D() {	// Конструктор
		max = 1;
		arr = new Point2D * [max];
		init();
		printf("Figure2D()\n");
	}
	Figure2D(int count) {	// Конструктор
		max = count;
		arr = new Point2D * [max];
		init();
		printf("Figure2D(int count)\n");
	}
	Figure2D(const Figure2D& figure) {	// Конструктор копирования
		arr = new Point2D * [figure.max];
		for (int i = 0; i < max; ++i) {
			arr[i] = figure.arr[i];
		}
		printf("Figure2D(const Figure2D& figure)\n");
	}
	~Figure2D() {	// Деструктор
		for (int i = 0; i < max; ++i) {
			if (!isNull(i))
				delete arr[i];
			arr[i] = 0;
		}
		delete[] arr;
		printf("~Figure2D()\n");
	}
	void add(Point2D* point) {	// Добавление элемента
		int pos = 0;
		while (!isNull(pos) && pos < max) {
			pos++;
		}
		if (pos == max) {
			max++;
			Point2D** tmp = new Point2D * [max];
			for (int i = 0; i < max - 1; ++i) {
				tmp[i] = arr[i];
			}
			delete[] arr;
			arr = tmp;
		}
		arr[pos] = point;
	}
	void setObject(int pos, Point2D* point) {	// Изменение элемента
		arr[pos] = point;
	}
	Point2D& getObject(int pos) {	// Получение элемента
		return *arr[pos];
	}
	void delObject(int pos) {	// Удаление объекта
		delete arr[pos];
		arr[pos] = 0;
	}
	int getCount() {	// Получение объекта
		return max;
	}
	bool isNull(int pos) {	// Проверка наличия
		if (arr[pos] == 0)
			return true;
		return false;
	}
private:
	void init() {	// Инициализация элементов
		for (int i = 0; i < max; ++i) {
			arr[i] = 0;
		}
	}
};

int main()
{

	return 0;
}