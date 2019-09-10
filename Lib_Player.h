#pragma once

#include <iostream> 
#include <SFML/Graphics.hpp>

using namespace sf;
class Player { // класс Игрока
public:
	float mem_x, mem_y, x, y, w, h, dx, dy, speed = 0; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	String File; //файл с расширением
	Image image;//сфмл изображение
	Texture texture;//сфмл текстура
	Sprite sprite;//сфмл спрайт
	bool isMove = 0;
	float CurrentFrame = 0;
	enum { left, right, up, down, jump, stay } state;//добавляем тип перечисления - состояние объекта

	Player(String F, float X, float Y, float W, float H) {  //Конструктор с параметрами(формальными) для класса Player. При создании объекта класса мы будем задавать имя файла, координату Х и У, ширину и высоту
		state = left; 
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile("image/" + File);//запихиваем в image наше изображение вместо File мы передадим то, что пропишем при создании объекта. В нашем случае "hero.png" и получится запись идентичная 	image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(41, 33, 59));//убираем ненужный темно-синий цвет, эта тень мне показалась не красивой.
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y;//координата появления спрайта
		sprite.setTextureRect(IntRect(0, 0, w, h));  //Задаем спрайту один прямоугольник для вывода одного льва, а не кучи львов сразу. IntRect - приведение типов
		sprite.setOrigin(w / 2, h / 2);
	}

	void update(float time) //функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	{
		switch (state)//тут делаются различные действия в зависимости от состояния
		{
			case right:dx = speed; dy = 0;  break; //состояние идти вправо
			case left: dx = -speed; dy = 0; break;//состояние идти влево
			case up:   dx = 0; dy = -speed;   break;//будет состояние поднятия наверх (например по лестнице)
			case down: dx = 0; dy = speed;  break;//будет состояние во время спуска персонажа (например по лестнице)
			case jump: break;//здесь может быть вызов анимации
			case stay: break;//и здесь тоже		
		}
		x += dx*time;
		y += dy*time;
		if (!isMove) speed = 0;
		sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		

		if (x > 900) { x = 0; } 
		if (x < 0) { x = 900; }
		if (y > 500) { y = 0; }
		if (y < 0) { y = 500; }
	}
	void moving(float time)
	{
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left; speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(w * int(CurrentFrame), h, w, h)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right; speed = 0.1;//направление вправо, см выше
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(w * int(CurrentFrame), h*2, w, h)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			state = up; speed = 0.1;//направление вниз, см выше
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(w* int(CurrentFrame), h*3, w, h)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) { //если нажата клавиша стрелка влево или англ буква А
			state = down; speed = 0.1;//направление вверх, см выше
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			sprite.setTextureRect(IntRect(w * int(CurrentFrame), 0, w, h)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
		}

	}
};