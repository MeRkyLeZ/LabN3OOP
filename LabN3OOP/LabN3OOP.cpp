#include <iostream>
#include <time.h>
#include <chrono>

using namespace std;

class Point2D {	// Объект
protected:
	double x, y;
public:
	Point2D() {	// Конструктор
		x = 0;
		y = 0;
		//printf("Point2D()\n");
	}
	Point2D(double x, double y) {	// Конструктор
		this->x = x;
		this->y = y;
		//printf("Point2D(double x, double y)\n");
	}
	Point2D(const Point2D& point) {	// Конструктор копирования
		this->x = point.x;
		this->y = point.y;
		//printf("Point2D(const Point2D &point)\n");
	}
	~Point2D() {	// Деструктор
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
	void delObject(unsigned int pos) {	// Удаление объекта
		delete arr[pos];
		arr[pos] = 0;
		count--;
	}
	void setObject(unsigned int pos, Point2D* point) {	// Изменение элемента
		if (pos >= size) {
			size = pos + 1;
			Point2D** tmp = new Point2D * [size];
			for (int i = 0; i < size - 1; ++i) {
				tmp[i] = arr[i];
			}
			delete[] arr;
			arr = tmp;
		}
		delete arr[pos];
		arr[pos] = point;
	}
	Point2D& getObject(unsigned int pos) {	// Получение элемента
		return *arr[pos];
	}
	int getCount() {	// Получение количества объектов
		return count;
	}
	int getSize() {	// Получение размера хранилища
		return size;
	}
	bool isNull(unsigned int pos) {	// Проверка наличия
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

void randMethod(Point2D point) {	// Случайный метод объекта
	srand(time(0));
	int key = rand() % 4 + 1;
	switch (key) {	// Выполняем случайные методы
	case 1: point.getX(); break;
	case 2: point.getY(); break;
	case 3: point.setX(rand() % 51); break;
	case 4: point.setY(rand() % 51); break;
	}
}

void Test(int count) {	// Проверка работы
	Figure2D* figure;	// Создаем хранилище
	figure = new Figure2D(10);
	for (int i = 0; i < figure->getSize(); ++i)	// Добавляем в него объекты
		figure->setObject(i, new Point2D());
	for (int i = 0; i < count; ++i) {	// Обращаемся поочередно к элементам
		srand(time(0));
		int key = rand() % 7 + 1;
		switch (key) {	// Выполняем случайные методы
		case 1: figure->addObject(new Point2D); break;
		case 2: figure->delObject(rand() % (figure->getSize() - 1)); break;
		case 3: figure->setObject(rand() % (figure->getSize() - 1), new Point2D); break;
		case 4: randMethod(figure->getObject(rand() % (figure->getSize() - 1))); break;
		case 5: figure->getCount(); break;
		case 6: figure->getSize(); break;
		case 7: figure->isNull(rand() % (figure->getSize() - 1)); break;
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