#pragma once

#include "map.h"
#include "enemy.h"

using namespace sf;

class BOSS
{
public:
	float dx;
	int life;
	FloatRect rect;
	Sprite sprite;
	float y_end, currentFrame, h, w, beg_x, beg_y = 0;
	Texture texture;
	int max_anim, begin, end;
	float timeout;
	bool flag;
	void set(String file, int y, float begin_x, float begin_y, float H, float W, int max_animi, int begin_ob, int end_ob)
	{
		texture.loadFromFile("image/" + file);
		sprite.setTexture(texture);
		h = H; w = W; beg_x = begin_x; beg_y = begin_y; begin = end_ob; end = begin_ob;
		rect = FloatRect(begin, y, w, h);
		dx = 0.05; life = 20;
		timeout = 30; flag = false;
		currentFrame = 1; 
		max_anim = max_animi;
		sprite.setPosition(begin, y);
	}

	void update(float time)
	{
		Collision();
		currentFrame += time * 0.005;
		if (currentFrame > max_anim) currentFrame = 1;
		if (timeout == 30|| timeout < 0) {
			if (life>0) {
				max_anim = 4;
				rect.left += dx * time * 2;
				if (dx < 0) sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame) + w, beg_y, -w, h)); 
				if (dx > 0) sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame), beg_y, w, h));
			}
			if (timeout == 30 )timeout -= (time / 1000);
			else if ((rect.left >= begin) && (flag)) { timeout = 30; flag = false; }
		}
		else {
			max_anim = 3;
			sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame) + w, beg_y, -w, h));
			timeout -= (time / 1000);
		}
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}
	void Collision()
	{
		if (rect.left > begin) { dx = -0.05; }
		else if (rect.left < end) { dx = 0.05; flag = true; }

	}
};
