#pragma once

#include "map.h"

using namespace sf;

class OTHER
{
public:

	FloatRect rect;
	Sprite sprite;
	float currentFrame, h, w, beg_x, beg_y = 0;
	Texture texture;
	int max_anim = 0;
	void set(String file , int x, int y, float begin_x, float begin_y, float H, float W, int max_animi)
	{
		texture.loadFromFile("image/" + file);
		sprite.setTexture(texture);
		h = H; w = W; beg_x = begin_x; beg_y = begin_y;
		rect = FloatRect(x, y, w, h);
		currentFrame = 1;
		max_anim = max_animi;
		sprite.setPosition(x, y);
	}

	void update(float time)
	{
		currentFrame += time * 0.0005;
		if (currentFrame > max_anim) currentFrame = 1;

		sprite.setTextureRect(IntRect(beg_x + w * int(currentFrame), beg_y, -w, h));
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}

	/*void Collision()
	{

		for (int i = rect.top / 16; i<(rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j<(rect.left + rect.width) / 16; j++)
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == '0'))
				{
					if (dx>0)
					{
						rect.left = j * 16 - rect.width; dx *= -1;
					}
					else if (dx<0)
					{
						rect.left = j * 16 + 16;  dx *= -1;
					}

				}
	}*/

};
