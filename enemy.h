#pragma once
#include "map.h"

using namespace sf;

class ENEMY
{
public:
	bool onGround;
	float dx, dy;
	bool life;
	FloatRect rect;
	Sprite sprite;
	float y_end, currentFrame, h, w , beg_x, beg_y = 0;
	Texture texture;
	int max_anim, nomber_bot, begin, end;
	void set(String file,  int y, float begin_x, float begin_y, float H, float W, int max_animi, int nom, int begin_ob, int end_ob)
	{
		texture.loadFromFile("image/" + file);
		sprite.setTexture(texture);
		h = H; w = W; beg_x = begin_x; beg_y = begin_y; begin = begin_ob; end = end_ob;
		rect = FloatRect(begin_ob, y, w, h);
		dx = 0.05; dy = 0.0005; y_end = y;
		currentFrame = 1; nomber_bot = nom;
		max_anim = max_animi;
		life = true;
		sprite.setPosition(begin_ob, y);

		if (nomber_bot == 4) {
			begin = end_ob; end = begin_ob;
			rect = FloatRect(begin, y, w, h);
			sprite.setPosition(begin, y);
		}
	}

	void update(float time)
	{

		Collision();
		currentFrame += time * 0.005;
		if (currentFrame > max_anim) currentFrame = 1;

		if (life) {
			if (nomber_bot == 1) {
				rect.left += dx * time*2;
				if (dx < 0) sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame), beg_y, w, h));
				if (dx > 0) sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame) + w, beg_y, -w, h));
			}
			if (nomber_bot == 2) {
				rect.left += dx * time*2;
				if (dx < 0) sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame) + w, beg_y, -w, h)); 
				if (dx > 0) sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame), beg_y, w, h));
			}
			if (nomber_bot == 3) {
				rect.left += dx * time;
				rect.top += dy*time*2;
				if (dx>0) sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame), beg_y, w, h));
				if (dx<0) sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame) + w, beg_y, -w, h));
			}
			if (nomber_bot == 4) {
				rect.left += dx * time*2;
				if (dx < 0) sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame) + w, beg_y, -w, h));
				if (dx > 0) sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame), beg_y, w, h));
			}
		}
		//if (!life) sprite.setTextureRect(IntRect(58, 0, 16, 16));
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}

	void Collision()
	{
		if (nomber_bot == 4)
		{
			if (rect.left >= begin) { dx = -0.05; }
			else if (rect.left <= end) { rect.left = begin; }
		}
		else {
			if (rect.left < begin) { dx = 0.05; }
			else if (rect.left > end) { dx = -0.05; }
			if (nomber_bot == 3)
			{
				if (rect.top > y_end) { dy = -0.026; }
				else if (rect.top < (y_end - 100)) { dy = 0.026; }
			}
		}
	}
};


void collis( PLAYER &hero, ENEMY *bot, const int count) {
	for (int i = 0; i < count; i++) {
		if (hero.rect.intersects(bot[i].rect))
		{
			if (bot[i].life) {
				if (hero.dy > 0) { bot[i].dx = 0; hero.dy = -0.2; bot[i].life = false; }
				else {
					if (hero.life > 0) {
						if (hero.count_collis > 5) { hero.life--; hero.count_collis = 0; hero.rect.left -= 100; }
						else hero.count_collis++;
					}
				}
			}
		}
	}

}