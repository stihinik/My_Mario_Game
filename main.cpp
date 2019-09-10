
#include "Player.h"
#include "enemy.h"
#include "text_work.h"
#include "other_anim.h"
#include "statice_pic.h"
#include "boss.h"

bool startGame() {

	bool prol = true;
	int epilog = 1;
	int end = 0;
	float stop = 0;
	RenderWindow window(VideoMode(1200, 650), "Pavel_Game!");

	Texture tileSet;
	tileSet.loadFromFile("image/Mario_tileset.png");
	Sprite tile(tileSet);

	//главный герой(игрок)
	PLAYER Mario("all_unity.png",30, 400, 0, 0, 60, 41, 3);

	//обычные враги
	const int count_enemy_bot = 9;
	const int count_enemy_bird = 7;
	const int count_enemy_ninja = 3;
	const int count_enemy_skelet = 5;

	ENEMY  enemy_bot[count_enemy_bot];
	enemy_bot[0].set("all_unity.png", 535, 0, 65, 60, 82, 3, 1, 350, 610);
	enemy_bot[1].set("all_unity.png", 535, 0, 65, 60, 82, 3, 1, 930, 1200);
	enemy_bot[2].set("all_unity.png", 535, 0, 65, 60, 82, 3, 1, 1000, 1300);
	enemy_bot[3].set("all_unity.png", 535, 0, 65, 60, 82, 3, 1, 1100, 1380);
	enemy_bot[4].set("all_unity.png", 535, 0, 65, 60, 82, 3, 1, 2038, 2500);
	enemy_bot[5].set("all_unity.png", 535, 0, 65, 60, 82, 3, 1, 2100, 2675);
	enemy_bot[6].set("all_unity.png", 535, 0, 65, 60, 82, 3, 1, 5836, 6203);
	enemy_bot[7].set("all_unity.png", 535, 0, 65, 60, 82, 3, 1, 6208, 6434);
	enemy_bot[8].set("all_unity.png", 335, 0, 65, 60, 82, 3, 1, 6848, 7594);

	ENEMY  enemy_bird[count_enemy_bird];
	enemy_bird[0].set("all_unity.png", 250, 0, 120, 80, 110, 5, 2, 1880, 2500);
	enemy_bird[1].set("all_unity.png", 250, 0, 120, 80, 110, 5, 2, 2100, 2990);
	enemy_bird[2].set("all_unity.png", 372, 0, 120, 80, 110, 5, 2, 4320, 4800);
	enemy_bird[3].set("all_unity.png", 210, 0, 120, 80, 110, 5, 2, 5237, 5850);
	enemy_bird[4].set("all_unity.png", 210, 0, 120, 80, 110, 5, 2, 5850, 6650);
	enemy_bird[5].set("all_unity.png", 210, 0, 120, 80, 110, 5, 2, 8090, 8995);
	enemy_bird[6].set("all_unity.png", 210, 0, 120, 80, 110, 5, 2, 8995, 10040);

	ENEMY  enemy_ninja[count_enemy_ninja];
	enemy_ninja[0].set("all_unity.png", 530, 0, 200, 67, 58, 6, 3, 6680, 6810);
	enemy_ninja[1].set("all_unity.png", 480, 0, 200, 67, 58, 6, 3, 8650, 8780);
	enemy_ninja[2].set("all_unity.png", 465, 0, 200, 67, 58, 6, 3, 9330, 9460);
	for (int i = 0; i < count_enemy_bot; i++)enemy_bot[i].sprite.setScale(0.5, 0.5);
	for (int i = 0; i < count_enemy_ninja; i++)enemy_ninja[i].sprite.setScale(0.5, 0.5);

	ENEMY skelet[count_enemy_skelet];
	for (int i = 0; i < count_enemy_skelet; i++)skelet[i].set("all_unity.png", 520, 0, 275, 40, 45, 9, 4, 10630, 11400);
	BOSS monkey;
	monkey.set("all_unity.png", 470, 0, 320, 90, 114, 4, 10630, 11400);

	//статические анимации
	OTHER princess;
	princess.set("all_unity.png", 11410, 325, 0, 530, 65, 46, 4);

	const int count_fire= 12;
	OTHER fire[count_fire];
	fire[0].set("fire_one.png", 680, 550, 0, 0, 160, 170, 6);
	fire[1].set("fire_one.png", 610, 550, 0, 0, 160, 170, 6);

	fire[2].set("fire_one.png", 3120, 550, 0, 0, 160, 170, 6);
	fire[3].set("fire_one.png", 3050, 550, 0, 0, 160, 170, 6);

	fire[4].set("fire_one.png", 3290, 550, 0, 0, 160, 170, 6);
	fire[5].set("fire_one.png", 3220, 550, 0, 0, 160, 170, 6);

	fire[6].set("fire_one.png", 3430, 550, 0, 0, 160, 170, 6);
	fire[7].set("fire_one.png", 3360, 550, 0, 0, 160, 170, 6);

	fire[8].set("fire_one.png", 6710, 550, 0, 0, 160, 170, 6);
	fire[9].set("fire_one.png", 6640, 550, 0, 0, 160, 170, 6);

	fire[10].set("fire_one.png", 7520, 550, 0, 0, 160, 170, 6);
	fire[11].set("fire_one.png", 7450, 550, 0, 0, 160, 170, 6);
	//картинки без анимации
	Picture sky;
	sky.set("sky_small.png", 0, 0);
	Picture life[3];
	for (int i = 0; i < 3; i++) {
		life[i].set("heart.png", 0 + 50 * i, 150);
		life[i].sprite.setColor(Color::Green);
		life[i].sprite.setScale(0.6, 0.6);
	}
	Picture mag;
	mag.set("boy.png", 600, 0);
	Picture I;
	I.set("pavel.png", 800, 100);
	I.sprite.setScale(0.5, 0.5);

	Picture lord;
	lord.set("lord.png", 500, 0);
	Picture cenderella;
	cenderella.set("cenderella.png", 600, 0);
	Picture evil_cenderella;
	evil_cenderella.set("UI.png", 600, 0);
	Picture list;
	list.set("missi.jpg", 100, 100);
	Picture castle;
	castle.set("castle1.png", 980, 390);
	//музыка
	Music music;
	music.openFromFile("mama_mia.ogg");
	Music boss;
	boss.openFromFile("dancing_queen.ogg");

	//текст 
	Font font;
	font.loadFromFile("CyrilicOld.ttf");

	Text text_life_boss("", font, 20);
	text_get(text_life_boss, " ", 1100, 450);
	text_life_boss.setFillColor(Color::Red);

	String text_gameover[3] = { "Конец Игры" ,"Нажмите Tab чтобы перезагрузить игру","Нажмите ESC чтобы выйти из игры"};
	Text text_game("", font, 40);
	text_get(text_game, "", 30, 300);

	Text text_prolog("", font, 18);

	Clock clock;

	for (int i = 0; i < H; i++)TileMap[i] = TileMap_1[i] + TileMap_2[i] + TileMap_3[i];

	while (window.isOpen())
	{
		//monkey.life = 0;

		float time = clock.getElapsedTime().asMicroseconds(); 
		clock.restart(); 
		time = time / 600; 
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
				return false;
			}
		}
		
		collis(Mario, enemy_bot, count_enemy_bot);
		collis(Mario, enemy_bird, count_enemy_bird);
		collis(Mario, enemy_ninja, count_enemy_ninja);

		for (int i = 0; i < count_enemy_skelet; i++) {
			if (Mario.rect.intersects(skelet[i].rect))
			{
				if (skelet[i].life) {
					if (Mario.dy > 0) { skelet[i].dx = 0; Mario.dy = -0.2; skelet[i].life = false; monkey.life--; }
					else {
						if (Mario.life > 0) {
							if (Mario.count_collis > 5) { Mario.life--; Mario.count_collis = 0; Mario.rect.left = 10560; Mario.rect.top = 500;}
							else Mario.count_collis++;
						}
					}
				}
			}
		}
		if (Mario.rect.intersects(monkey.rect))
		{
			if (Mario.life > 0) {
				if (Mario.count_collis > 6) { Mario.life--; Mario.count_collis = 0; Mario.rect.left = 10560; Mario.rect.top = 500;}
				else Mario.count_collis++;
			}		
		}

		if (Mario.rect.left>200 && Mario.rect.left < 10500) offsetX = Mario.rect.left - 200; //смещение камеры

		window.clear(Color(107, 140, 255));
		window.draw(sky.sprite);
		if (monkey.life != 0) {
			if (prol)
			{
				window.draw(mag.sprite);
				window.draw(list.sprite);
				for (int i = 0; i < 23; i++) {
					text_get(text_prolog, prolog[i], 120, 110 + 20 * i);
					text_prolog.setFillColor(Color::Black);
					if (i == 22)text_prolog.setFillColor(Color::Red);
					window.draw(text_prolog);
					if (Keyboard::isKeyPressed(Keyboard::Space)) { prol = false; music.play(); }
				}
			}
			else {
				if ((Mario.rect.left < 10450))
				{
					for (int i = 0; i < Mario.life; i++) window.draw(life[i].sprite);
					for (int i = 0; i < count_enemy_bot; i++) if (enemy_bot[i].life) window.draw(enemy_bot[i].sprite);
					for (int i = 0; i < count_enemy_bird; i++) if (enemy_bird[i].life) window.draw(enemy_bird[i].sprite);
					for (int i = 0; i < count_enemy_ninja; i++) if (enemy_ninja[i].life) window.draw(enemy_ninja[i].sprite);
					for (int i = 0; i < count_fire; i++) window.draw(fire[i].sprite);
				}
				else if (Mario.rect.top > 300) {
					if (epilog < 90) {
						if (epilog < 10) {
							window.draw(lord.sprite);
							window.draw(list.sprite);
							for (int i = 0; i < 10; i++) {
								text_get(text_prolog, monolog_evil[i], 120, 110 + 30 * i);
								text_prolog.setFillColor(Color::Black);
								if (i == 9)text_prolog.setFillColor(Color::Red);
								window.draw(text_prolog);
								if (Keyboard::isKeyPressed(Keyboard::Space)) { epilog++; }
							}
						}
						else if (epilog >= 10 && epilog <= 50) {
							window.draw(cenderella.sprite);
							window.draw(list.sprite);
							for (int i = 0; i < 2; i++) {
								text_get(text_prolog, monolog_prin[i], 120, 110 + 40 * i);
								text_prolog.setFillColor(Color::Black);
								if (i == 1)text_prolog.setFillColor(Color::Red);
								window.draw(text_prolog);
							}
							if (Keyboard::isKeyPressed(Keyboard::Space)) { epilog++; }
						}
						else if (epilog > 50 && epilog < 90) {
							window.draw(mag.sprite);
							window.draw(list.sprite);
							for (int i = 0; i < 13; i++) {
								text_get(text_prolog, monolog_mag[i], 120, 110 + 30 * i);
								text_prolog.setFillColor(Color::Black);
								if (i == 12)text_prolog.setFillColor(Color::Red);
								window.draw(text_prolog);
							}
							if (Keyboard::isKeyPressed(Keyboard::Space)) { epilog++; if (epilog == 89) { music.stop(); boss.play(); } }
						}
					}
					else {
						window.draw(castle.sprite);
						window.draw(princess.sprite);
						window.draw(monkey.sprite);
						if (skelet[0].life) { if (monkey.timeout >= 0) { window.draw(skelet[0].sprite); } }
						if (skelet[1].life) { if (monkey.timeout >= 0 && monkey.timeout < 25) { window.draw(skelet[1].sprite); } }
						if (skelet[2].life) { if (monkey.timeout >= 0 && monkey.timeout < 18) { window.draw(skelet[2].sprite); } }
						if (skelet[3].life) { if (monkey.timeout >= 0 && monkey.timeout < 12) { window.draw(skelet[3].sprite); } }
						if (skelet[4].life) { if (monkey.timeout >= 0 && monkey.timeout < 8) { window.draw(skelet[4].sprite); } }
						window.draw(text_life_boss);
					}
				}
				if ((Mario.rect.left < 10600) || epilog >= 90) {
					window.draw(Mario.sprite);
					for (int i = 0; i < H; i++)
						for (int j = 0; j < W; j++)
						{
							if (TileMap[i][j] == 'P')  tile.setTextureRect(IntRect(143 - 16 * 3, 112, 17, 16));

							if (TileMap[i][j] == 'k')  tile.setTextureRect(IntRect(0, 26, 27, 21));

							if (TileMap[i][j] == 'c')  tile.setTextureRect(IntRect(143 - 16, 112, 16, 16));

							if (TileMap[i][j] == 't')  tile.setTextureRect(IntRect(0, 50, 42, 95 - 47));

							if (TileMap[i][j] == 'G')  tile.setTextureRect(IntRect(50, 59, 43, 22));

							if (TileMap[i][j] == 'd')  tile.setTextureRect(IntRect(0, 100, 45, 40));

							if (TileMap[i][j] == 'w')  tile.setTextureRect(IntRect(99, 224, 140 - 99, 255 - 224));

							if (TileMap[i][j] == 'r')  tile.setTextureRect(IntRect(34, 26, 27, 18));
							if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0')) continue;

							tile.setPosition(j * 16 - offsetX, i * 16 - offsetY);

							window.draw(tile);
						}
					window.draw(text_life_boss);
					for (int i = 0; i < Mario.life; i++) window.draw(life[i].sprite);
				}

				if (Mario.life == 0) {
					text_get(text_game, text_gameover[0], 500, 200);
					text_game.setFillColor(Color::Red);
					window.draw(text_game);
					text_get(text_game, text_gameover[1], 250, 250);
					text_game.setFillColor(Color::Red);
					window.draw(text_game);
					text_get(text_game, text_gameover[2], 300, 300);
					text_game.setFillColor(Color::Red);
					window.draw(text_game);
				}
				else {
					Mario.update(time);
					if ((Mario.rect.left < 10450))
					{
						for (int i = 0; i < count_enemy_bot; i++) enemy_bot[i].update(time);
						for (int i = 0; i < count_enemy_bird; i++) enemy_bird[i].update(time);
						for (int i = 0; i < count_enemy_ninja; i++) enemy_ninja[i].update(time);
						for (int i = 0; i < count_fire; i++) fire[i].update(time*3);
					}
					else if (Mario.rect.top > 300) {
						if (epilog >= 90) {
							text_transfer(text_life_boss, " ", monkey.life);
							princess.update(time * 2);
							monkey.update(time);
							if (monkey.timeout >= 0) { skelet[0].update(time); }
							if (monkey.timeout >= 0 && monkey.timeout < 25) { skelet[1].update(time); }
							if (monkey.timeout >= 0 && monkey.timeout < 18) { skelet[2].update(time); }
							if (monkey.timeout >= 0 && monkey.timeout < 12) { skelet[3].update(time); }
							if (monkey.timeout >= 0 && monkey.timeout < 8)  { skelet[4].update(time); }
							if (monkey.timeout < 0) {
								for (int i = 0; i < count_enemy_skelet; i++) {
									skelet[i].rect.left = 11400; skelet[i].life = true;
								}
							}
						}
					}
				}
			}
		}
		else {
			stop += (time / 1000);
			if (end == 0) {
				window.draw(I.sprite);
				window.draw(list.sprite);
				for (int i = 0; i < 10; i++) {
					text_get(text_prolog, end_I[i], 120, 110 + 30 * i);
					text_prolog.setFillColor(Color::Black);
					if (i > 5)text_prolog.setFillColor(Color::Red);
					window.draw(text_prolog);
				}
				if (Keyboard::isKeyPressed(Keyboard::Home) && stop <= 30) { end = 1; }
				if (Keyboard::isKeyPressed(Keyboard::End) && stop <= 30) { end = 2; }
				if (stop > 30) { end = 3; }
			}
			if (end == 1) {
				window.draw(cenderella.sprite);
				window.draw(list.sprite);
				for (int i = 0; i < 2; i++) {
					text_get(text_prolog, end_prin[i], 120, 110 + 30 * i);
					text_prolog.setFillColor(Color::Black);
					if (i == 1)text_prolog.setFillColor(Color::Red);
					window.draw(text_prolog);
				}
				if (Keyboard::isKeyPressed(Keyboard::Space)) { end = 4; }
			}
			if (end == 2) {
				window.draw(evil_cenderella.sprite);
				window.draw(list.sprite);
				for (int i = 0; i < 6; i++) {
					text_get(text_prolog, end_evil_prin[i], 120, 110 + 30 * i);
					text_prolog.setFillColor(Color::Black);
					if (i == 5)text_prolog.setFillColor(Color::Red);
					window.draw(text_prolog);
				}
				if (Keyboard::isKeyPressed(Keyboard::Space)) { end = 4; }
			}
			if (end == 3) {
				window.draw(I.sprite);
				window.draw(list.sprite);
				for (int i = 0; i < 6; i++) {
					text_get(text_prolog, my_end[i], 120, 110 + 30 * i);
					text_prolog.setFillColor(Color::Black);
					if (i == 5)text_prolog.setFillColor(Color::Red);
					window.draw(text_prolog);
				}
				if (Keyboard::isKeyPressed(Keyboard::Space)) { end = 4; }
			}
			if (end == 4) {
				text_get(text_game, text_gameover[0], 500, 200);
				text_game.setFillColor(Color::Red);
				window.draw(text_game);
				text_get(text_game, text_gameover[1], 250, 250);
				text_game.setFillColor(Color::Red);
				window.draw(text_game);
				text_get(text_game, text_gameover[2], 300, 300);
				text_game.setFillColor(Color::Red);
				window.draw(text_game);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Tab)) { offsetX = 0, offsetY = 0; return true; }
		if (Keyboard::isKeyPressed(Keyboard::Escape)) { return false; }
		window.display();
	}
}

void gameRunning() {
	if (startGame()) { gameRunning(); }
}

int main()
{
	gameRunning();//запускаем процесс игры
	return 0;
}



