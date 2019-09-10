#pragma once

#include "map.h"

using namespace sf;

class PLAYER {

public:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame, h, w , beg_x,beg_y = 0;
	Texture texture;
	int max_anim;
	int life,count_collis;
	PLAYER(String file, int x, int y,float begin_x, float begin_y, float H, float W, int max_animi)
	{
		texture.loadFromFile("image/" + file);
		sprite.setTexture(texture);//заливаем спрайт текстуро
		h = H; w = W; beg_x = begin_x; beg_y = begin_y;
		dx = dy = 0.1; life = 3; count_collis = 0;
		rect = FloatRect(x, y, w, h);
		currentFrame = 1; 
		max_anim = max_animi;
		sprite.setPosition(x, y);
	}
	void update(float time)
	{
		if (Keyboard::isKeyPressed(Keyboard::Left))    dx = -0.1;
		if (Keyboard::isKeyPressed(Keyboard::Right))   dx = 0.1;
		if (Keyboard::isKeyPressed(Keyboard::Space))if (onGround) { dy = -0.27; onGround = false; }

		rect.left += dx * time;
		Collision(0);
		if (!onGround) dy = dy + 0.0005*time;
		rect.top += dy*time;
		onGround = false;
		Collision(1);
		currentFrame += time * 0.005;
		if (currentFrame > max_anim) currentFrame = 1;
		if (dx>0) sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame), beg_y, w, h));
		if (dx<0) sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame) + w, beg_y, -w, h));
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
		dx = 0;
	}


	void Collision(int num)
	{
		if (rect.top < 545) {
			for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
				for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
				{
					if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't') || (TileMap[i][j] == 'd'))
					{
						if (dy > 0 && num == 1)
						{
							rect.top = i * 16 - rect.height;  dy = 0;   onGround = true;
						}
						if (dy < 0 && num == 1)
						{
							rect.top = i * 16 + 16;   dy = 0;
						}
						if (dx > 0 && num == 0)
						{
							rect.left = j * 16 - rect.width;
						}
						if (dx < 0 && num == 0)
						{
							rect.left = j * 16 + 16;
						}
					}

					if (TileMap[i][j] == 'c') {
						TileMap[i][j] = ' ';
					}
				}
		}
		else {
			life--; rect.left -= 100; rect.top = 400;
		}
	}

};
