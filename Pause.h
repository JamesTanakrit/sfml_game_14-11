#include"AllHeader.h"
#include"Button.h"

class Pause
{
private:
	Button resumeButton;
	Button exitToMenuButton;
	Button quitButton;
	Texture pause;
	Sprite sprite;

public:
	inline Pause()
	{
		resumeButton.setup(Vector2f(466, 430), Vector2f(356, 96), nullptr, "", Color(0, 0, 0, 0), Color(0, 0, 0, 50), Color(0, 0, 0, 100));
		exitToMenuButton.setup(Vector2f(466, 591), Vector2f(356, 96), nullptr, "", Color(0, 0, 0, 0), Color(0, 0, 0, 50), Color(0, 0, 0, 100));
		quitButton.setup(Vector2f(466, 753), Vector2f(356, 96), nullptr, "", Color(0, 0, 0, 0), Color(0, 0, 0, 50), Color(0, 0, 0, 100));
		resumeButton.isActive = true;
		exitToMenuButton.isActive = true;
		quitButton.isActive = true;
		pause.loadFromFile("testPause.png");
		sprite.setTexture(pause);
	}

	inline void update(RenderWindow& window)
	{
		Vector2f mousePos = Vector2f(Mouse::getPosition(window));
		resumeButton.update(mousePos, setRun, true);
		exitToMenuButton.update(mousePos, pauseRun, true);
		quitButton.update<RenderWindow>(mousePos, &window, &RenderWindow::close);
	}

	inline void render(RenderWindow& window)
	{
		window.draw(sprite);
		resumeButton.render(window);
		exitToMenuButton.render(window);
		quitButton.render(window);
	}

};