#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Picture{ // класс Игрока
public:
	//работа с мышью
	int tempX = 0;//временная коорд Х.Снимаем ее после нажатия прав клав мыши
	int tempY = 0;//коорд Y
	float distance = 0;//это расстояние от объекта до тыка курсора
	float dX = 0;//корректировка нажатия по х
	float dY = 0;//по у
	bool isMove, isSelect;//добавили переменные состояния движения и выбора объекта

	float x, y= 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
	void set(String F, float X, float Y) {  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		isMove = false; isSelect = false;
		File = F;//имя файла+расширение
		image.loadFromFile("image/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y;//координата появления спрайта
		sprite.setPosition(x, y);
	}
	void click(Event event, Vector2f pos)
	{
		if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
			if (event.key.code == Mouse::Left) {//а именно левая
				if (sprite.getGlobalBounds().contains(pos.x, pos.y))//и при этом координата курсора попадает в спрайт
				{
					sprite.setColor(Color::Green);//красим спрайт в зеленый,тем самым говоря игроку,что он выбрал персонажа и может сделать ход
					isSelect = true;
				}
			}
		if (isSelect)//если выбрали объект
			if (event.type == Event::MouseButtonPressed)//если нажата клавиша мыши
				if (event.key.code == Mouse::Right) {//а именно правая
					isMove = true;//то начинаем движение
					isSelect = false;//объект уже не выбран
					sprite.setColor(Color::White);//возвращаем обычный цвет спрайту
					tempX = pos.x;//забираем координату нажатия курсора Х
					tempY = pos.y;//и Y
				}
	}
	void moving(float time) {
		if (isMove) {
			distance = sqrt((tempX - x)*(tempX - x) + (tempY - y)*(tempY - y));//считаем дистанцию (расстояние от точки А до точки Б). используя формулу длины вектора
			if (distance > 2) {//этим условием убираем дергание во время конечной позиции спрайта
				x += 0.1*time*(tempX - x) / distance;//идем по иксу с помощью вектора нормали
				y += 0.1*time*(tempY - y) / distance;//идем по игреку так же
			}
			else { isMove = false; }//говорим что уже никуда не идем и выводим веселое сообщение в консоль
		}
		x += dX*2*time;
		y += dY*2*time;
		sprite.setPosition(x , y ); //задаем позицию спрайта в место его центра
	}

};