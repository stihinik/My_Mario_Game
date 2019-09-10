#pragma once

#include <iostream> 
#include <SFML/Graphics.hpp>

using namespace sf;
class Player { // ����� ������
public:
	float mem_x, mem_y, x, y, w, h, dx, dy, speed = 0; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	String File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������
	bool isMove = 0;
	float CurrentFrame = 0;
	enum { left, right, up, down, jump, stay } state;//��������� ��� ������������ - ��������� �������

	Player(String F, float X, float Y, float W, float H) {  //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
		state = left; 
		File = F;//��� �����+����������
		w = W; h = H;//������ � ������
		image.loadFromFile("image/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
		image.createMaskFromColor(Color(41, 33, 59));//������� �������� �����-����� ����, ��� ���� ��� ���������� �� ��������.
		texture.loadFromImage(image);//���������� ���� ����������� � ��������
		sprite.setTexture(texture);//�������� ������ ���������
		x = X; y = Y;//���������� ��������� �������
		sprite.setTextureRect(IntRect(0, 0, w, h));  //������ ������� ���� ������������� ��� ������ ������ ����, � �� ���� ����� �����. IntRect - ���������� �����
		sprite.setOrigin(w / 2, h / 2);
	}

	void update(float time) //������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	{
		switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		{
			case right:dx = speed; dy = 0;  break; //��������� ���� ������
			case left: dx = -speed; dy = 0; break;//��������� ���� �����
			case up:   dx = 0; dy = -speed;   break;//����� ��������� �������� ������ (�������� �� ��������)
			case down: dx = 0; dy = speed;  break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
			case jump: break;//����� ����� ���� ����� ��������
			case stay: break;//� ����� ����		
		}
		x += dx*time;
		y += dy*time;
		if (!isMove) speed = 0;
		sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		

		if (x > 900) { x = 0; } 
		if (x < 0) { x = 900; }
		if (y > 500) { y = 0; }
		if (y < 0) { y = 500; }
	}
	void moving(float time)
	{
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			state = left; speed = 0.1;//dir =1 - ����������� �����, speed =0.1 - �������� ��������. �������� - ����� �� ��� ����� �� �� ��� �� �������� � ����� �� ���������� ������ ���
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(w * int(CurrentFrame), h, w, h)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			state = right; speed = 0.1;//����������� ������, �� ����
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(w * int(CurrentFrame), h*2, w, h)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			state = up; speed = 0.1;//����������� ����, �� ����
			CurrentFrame += 0.005*time;
			if (CurrentFrame > 3) CurrentFrame -= 3;
			sprite.setTextureRect(IntRect(w* int(CurrentFrame), h*3, w, h)); //����� ������ p ������ player ������ ������, ����� �������� (��������� �������� �����)
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) { //���� ������ ������� ������� ����� ��� ���� ����� �
			state = down; speed = 0.1;//����������� �����, �� ����
			CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			sprite.setTextureRect(IntRect(w * int(CurrentFrame), 0, w, h)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
		}

	}
};