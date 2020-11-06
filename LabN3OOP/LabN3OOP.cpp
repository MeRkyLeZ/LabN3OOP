#include <iostream>
#include <time.h>
#include <chrono>

using namespace std;

class Point2D {
protected:
	double x, y;
public:
	Point2D() {
		x = 0;
		y = 0;
		//printf("Point2D()\n");
	}
	Point2D(double x, double y) {
		this->x = x;
		this->y = y;
		//printf("Point2D(double x, double y)\n");
	}
	Point2D(const Point2D& point) {
		this->x = point.x;
		this->y = point.y;
		//printf("Point2D(const Point2D &point)\n");
	}
	~Point2D() {
		//printf("~Point2D()\n");
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
	void setY(double y) {
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
		//printf("Figure2D()\n");
	}
	Figure2D(unsigned int size) {	// Конструктор
		this->size = size;
		count = 0;
		arr = new Point2D * [size];
		init();
		//printf("Figure2D(int size)\n");
	}
	Figure2D(const Figure2D& figure) {	// Конструктор копирования
		arr = new Point2D * [figure.size];
		this->size = figure.size;
		this->count = figure.count;
		for (int i = 0; i < size; ++i) {
			arr[i] = new Point2D(*figure.arr[i]);
		}
		//printf("Figure2D(const Figure2D& figure)\n");
	}
	~Figure2D() {	// Деструктор
		for (int i = 0; i < size; ++i) {
			if (!isNull(i))
				delete arr[i];
			arr[i] = 0;
		}
		delete[] arr;
		//printf("~Figure2D()\n");
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

void Test(int count) {	// Проверка работы
	// создаем хранилище
	Figure2D* figure;
	figure = new Figure2D(count);
	// добавляем в него объекты
	for (int i = 0; i < figure->getSize(); ++i)
		figure->setObject(i, new Point2D());
	// обращаемся поочередно к элементам
	for (int i = 0; i < figure->getSize(); ++i) {
		srand(time(0));
		int key = rand() % 4 + 1;
		switch (key) {
		case 1: figure->getObject(i).setX(rand() % 51); break;
		case 2: figure->getObject(i).setY(rand() % 51); break;
		case 3: figure->getObject(rand() % figure->getSize() - 1).getX(); break;
		case 4: figure->getObject(rand() % figure->getSize() - 1).getY(); break;
		}
	}
	delete figure;
}



int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "100:" << endl;
	auto start = chrono::high_resolution_clock::now();	// Начало отсчета времени
	Test(100);
	auto end = chrono::high_resolution_clock::now();	// Конец отсчета времени
	chrono::duration<float> duration = end - start;
	cout << "Время работы = " << duration.count() << " сек." << endl;
	start = chrono::high_resolution_clock::now();	// Начало отсчета времени
	cout << "1000:" << endl;
	end = chrono::high_resolution_clock::now();	// Конец отсчета времени
	duration = end - start;
	Test(1000);
	cout << "Время работы = " << duration.count() << " сек." << endl;
	cout << "10000:" << endl;
	start = chrono::high_resolution_clock::now();	// Начало отсчета времени
	Test(10000);
	end = chrono::high_resolution_clock::now();	// Конец отсчета времени
	duration = end - start;
	cout << "Время работы = " << duration.count() << " сек." << endl;
	return 0;
}