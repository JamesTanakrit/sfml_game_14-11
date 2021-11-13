#pragma once
#include"AllHeader.h"
#include"Button.h"

class gameOver
{
private:
	Button continueButton;
	Texture gameOverPic;
	Sprite sprite;

public:
	inline gameOver()
	{
		continueButton.setup(Vector2f(466, 430), Vector2f(356, 96), nullptr, "", Color(0, 0, 0, 0), Color(0, 0, 0, 50), Color(0, 0, 0, 100));
		continueButton.isActive = true;
		gameOverPic.loadFromFile("testEnd.png");
		sprite.setTexture(gameOverPic);
	}

	inline void update(RenderWindow& window)
	{
		Vector2f mousePos = Vector2f(Mouse::getPosition(window));
		continueButton.update(mousePos, setRun, true);
	}

	inline void render(RenderWindow& window)
	{
		window.draw(sprite);
		continueButton.render(window);
	}

};
