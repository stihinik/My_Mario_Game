#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Picture{ // ����� ������
public:
	//������ � �����
	int tempX = 0;//��������� ����� �.������� �� ����� ������� ���� ���� ����
	int tempY = 0;//����� Y
	float distance = 0;//��� ���������� �� ������� �� ���� �������
	float dX = 0;//������������� ������� �� �
	float dY = 0;//�� �
	bool isMove, isSelect;//�������� ���������� ��������� �������� � ������ �������

	float x, y= 0; //���������� ������ � � �, ������ ������, ��������� (�� � � �� �), ���� ��������
	String File; //���� � �����������
	Image image;//���� �����������
	Texture texture;//���� ��������
	Sprite sprite;//���� ������
	void set(String F, float X, float Y) {  //����������� � �����������(�����������) ��� ������ Player. ��� �������� ������� ������ �� ����� �������� ��� �����, ���������� � � �, ������ � ������
		isMove = false; isSelect = false;
		File = F;//��� �����+����������
		image.loadFromFile("image/" + File);//���������� � image ���� ����������� ������ File �� ��������� ��, ��� �������� ��� �������� �������. � ����� ������ "hero.png" � ��������� ������ ���������� 	image.loadFromFile("images/hero/png");
		texture.loadFromImage(image);//���������� ���� ����������� � ��������
		sprite.setTexture(texture);//�������� ������ ���������
		x = X; y = Y;//���������� ��������� �������
		sprite.setPosition(x, y);
	}
	void click(Event event, Vector2f pos)
	{
		if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
			if (event.key.code == Mouse::Left) {//� ������ �����
				if (sprite.getGlobalBounds().contains(pos.x, pos.y))//� ��� ���� ���������� ������� �������� � ������
				{
					sprite.setColor(Color::Green);//������ ������ � �������,��� ����� ������ ������,��� �� ������ ��������� � ����� ������� ���
					isSelect = true;
				}
			}
		if (isSelect)//���� ������� ������
			if (event.type == Event::MouseButtonPressed)//���� ������ ������� ����
				if (event.key.code == Mouse::Right) {//� ������ ������
					isMove = true;//�� �������� ��������
					isSelect = false;//������ ��� �� ������
					sprite.setColor(Color::White);//���������� ������� ���� �������
					tempX = pos.x;//�������� ���������� ������� ������� �
					tempY = pos.y;//� Y
				}
	}
	void moving(float time) {
		if (isMove) {
			distance = sqrt((tempX - x)*(tempX - x) + (tempY - y)*(tempY - y));//������� ��������� (���������� �� ����� � �� ����� �). ��������� ������� ����� �������
			if (distance > 2) {//���� �������� ������� �������� �� ����� �������� ������� �������
				x += 0.1*time*(tempX - x) / distance;//���� �� ���� � ������� ������� �������
				y += 0.1*time*(tempY - y) / distance;//���� �� ������ ��� ��
			}
			else { isMove = false; }//������� ��� ��� ������ �� ���� � ������� ������� ��������� � �������
		}
		x += dX*2*time;
		y += dY*2*time;
		sprite.setPosition(x , y ); //������ ������� ������� � ����� ��� ������
	}

};