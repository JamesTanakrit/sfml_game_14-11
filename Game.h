#pragma once
#include"AllHeader.h"
#include"player.h"
#include"enemy.h"
#include"bullet.h"
#include"Item.h"
//#include "gameOver.h"

class Game
{
private:
	Clock clock;
	float deltaTime;
	Texture maptexture;
	Sprite map;
	Player player;
	vector<Bullet> bullets;
	float fireRate, fireRateMax, fireBuff, ogFireRate, fireTimer;
	vector<Enemy> enemies;
	float enemyRate, enemyRateMax;
	int EnemyNumMax;
	float EnemyPlusTimer;
	float enTimer;
	int ogUpperB, ogLowerB, newUpperB, newLowerB, UpperB, LowerB;
	vector<Item> items;
   /* gameOver gameOv;*/
    

public:
	inline Game() 
	{
		deltaTime = 0;
		maptexture.loadFromFile("map.png");
		map.setTexture(maptexture);
		fireRate = 0;
		fireRateMax = 0.5;
		fireBuff = 0.2;
		ogFireRate = 0.5;
		fireTimer = 0;
		enemyRate = 0;
		enemyRateMax = 0.7;
		EnemyNumMax = 5;
		EnemyPlusTimer = 0;
		enTimer = 0;
		ogUpperB = 150;
		ogLowerB = 80;
		newUpperB = 50;
		newLowerB = 50;
		UpperB = 150;
		LowerB = 80;
	}

	inline void update(RenderWindow& window)
	{
		deltaTime = clock.restart().asSeconds() * multiplier;
        fireTimer -= deltaTime;
        if (fireTimer < 0)
        {
            fireRateMax = ogFireRate;
        }

        enTimer -= deltaTime;
        if (enTimer < 0)
        {
            UpperB = ogUpperB;
            LowerB = ogLowerB;
        }


        //update
        player.update(deltaTime);

        //Update Bullet
        fireRate += deltaTime;
        enemyRate += deltaTime;
        EnemyPlusTimer += deltaTime;
        /*cout << EnemyPlusTimer << endl;
        cout << deltaTime << endl;*/

        //enemy เพิ่ม 1 ตัวต่อ 10วิ
        if (EnemyPlusTimer > 10)
        {
            EnemyNumMax += 1;
            EnemyPlusTimer = 0;
            /*cout << "test" << endl;*/
        }

        if (Mouse::isButtonPressed(Mouse::Left) && fireRate >= fireRateMax)
        {
            Vector2f mousePos = Vector2f(Mouse::getPosition(window));
            Vector2f playerPos = player.getPosition() + player.getSize() / 2.f - Vector2f(2.5f, 2.5f);
            bullets.push_back(Bullet(playerPos, mousePos - playerPos, 400.f));
            fireRate = 0;
        }

        for (size_t i = 0; i < bullets.size(); i++)
        {
            bullets[i].update(deltaTime);
            bool outLeft = bullets[i].getPosition().x + bullets[i].getSize().x < 0;
            bool outRight = bullets[i].getPosition().x > 1280;
            bool outTop = bullets[i].getPosition().y + bullets[i].getSize().y < 0;
            bool outDown = bullets[i].getPosition().y > 960;
            if (outLeft || outRight || outTop || outDown)
            {
                bullets.erase(bullets.begin() + i);
            }
        }

        //Update enemy

        if (enemies.size() < EnemyNumMax && enemyRate >= enemyRateMax)
        {
            int enSpd = randint(LowerB, UpperB);
            int enPos = randint(1, 4);
            if (enPos == 1)
            {
                enemies.push_back(Enemy(18.f, Vector2f(0, randint(228, 692)), enSpd));
            }
            if (enPos == 2)
            {
                enemies.push_back(Enemy(18.f, Vector2f(1240, randint(228, 692)), enSpd));
            }
            if (enPos == 3)
            {
                enemies.push_back(Enemy(18.f, Vector2f(randint(303, 937), 0), enSpd));
            }
            if (enPos == 4)
            {
                enemies.push_back(Enemy(18.f, Vector2f(randint(303, 937), 920), enSpd));
            }
            enemies[enemies.size() - 1].setPlayer(&player);
            enemyRate = 0;
        }

        for (size_t i = 0; i < enemies.size(); i++)
        {
            enemies[i].update(deltaTime);
            if (player.getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
            {
                enemies.erase(enemies.begin() + i);
                /*
                จบเกม ไปหน้า game over
                */
                /*gameOv.update(window);
                gameOv.render(window);*/

                break;
            }
            for (size_t j = 0; j < bullets.size(); j++)
            {
                if (bullets[j].getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
                {
                    int ranItem = randint(1, 10);
                    if (ranItem == 4)
                    {
                        items.push_back(Item(enemies[i].getPosition(), Vector2f(20, 20), randint(0, 2)));
                    }
                    enemies.erase(enemies.begin() + i);
                    bullets.erase(bullets.begin() + j);
                    break;
                }
             
            }
            
        }


        for (size_t i = 0; i < items.size(); i++)
        {
            items[i].update(deltaTime);
            if (items[i].isPickedUp(player.getGlobalBounds()))
            {
                // do something
                if (items[i].tag == BulletSpeed)
                {
                    fireRateMax = fireBuff;
                    fireTimer = 10;
                }
                if (items[i].tag == SlowEnemy)
                {
                    UpperB = newUpperB;
                    LowerB = newLowerB;
                    enTimer = 4;
                }
                if (items[i].tag == DoubleScore)
                {
                    //score*2 10sec
                }
                items.erase(items.begin() + i);
                continue;
            }
            if (items[i].died)
            {
                items.erase(items.begin() + i);
            }
        }
	}

    inline void render(RenderWindow& window)
    {
        window.draw(map);

        //draw

        //draw bullets
        for (size_t i = 0; i < bullets.size(); i++)
        {
            bullets[i].render(window);
        }

        //draw enemies
        for (size_t i = 0; i < enemies.size(); i++)
        {
            enemies[i].render(window);
        }

        //draw items
        for (size_t i = 0; i < items.size(); i++)
        {
            items[i].render(window);
        }

        player.render(window);
    }

};

