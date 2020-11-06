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
	unsigned int size;	// Размер массива
	int count;	// Количество элментво
public:
	Figure2D() {	// Конструктор
		size = 0;
		count = 0;
		arr = new Point2D * [size];
		init();
		printf("Figure2D()\n");
	}
	Figure2D(unsigned int size) {	// Конструктор
		this->size = size;
		count = 0;
		arr = new Point2D * [size];
		init();
		printf("Figure2D(int size)\n");
	}
	Figure2D(const Figure2D& figure) {	// Конструктор копирования
		arr = new Point2D * [figure.size];
		this->size = figure.size;
		this->count = figure.count;
		for (int i = 0; i < size; ++i) {
			arr[i] = new Point2D(*figure.arr[i]);
		}
		printf("Figure2D(const Figure2D& figure)\n");
	}
	~Figure2D() {	// Деструктор
		for (int i = 0; i < size; ++i) {
			if (!isNull(i))
				delete arr[i];
			arr[i] = 0;
		}
		delete[] arr;
		printf("~Figure2D()\n");
	}
	void addObject(Point2D* point) {	// Добавление элемента
		int pos = 0;
		while (!isNull(pos) && pos < size) {
			pos++;
		}
		if (pos == size) {
			size++;
			Point2D** tmp = new Point2D * [size];
			for (int i = 0; i < size - 1; ++i) {
				tmp[i] = arr[i];
			}
			delete[] arr;
			arr = tmp;
		}
		arr[pos] = point;
		count++;
	}
	void delObject(int pos) {	// Удаление объекта
		delete arr[pos];
		arr[pos] = 0;
		count--;
	}
	void setObject(int pos, Point2D* point) {	// Изменение элемента
		arr[pos] = point;
	}
	Point2D& getObject(int pos) {	// Получение элемента
		return *arr[pos];
	}
	int getCount() {	// Получение количества объектов
		return count;
	}
	int getSize() {	// Получение размера хранилища
		return size;
	}
	bool isNull(int pos) {	// Проверка наличия
		if (arr[pos] == 0)
			return true;
		return false;
	}
private:
	void init() {	// Инициализация элементов
		for (int i = 0; i < size; ++i) {
			arr[i] = 0;
		}
	}
};

int main()
{

	return 0;
}