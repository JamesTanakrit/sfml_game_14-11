#include "Game.h"
#include "Menu.h"
#include "Pause.h"

float multiplier = 1;
bool runGame = false;
bool goPause = false;

int main()
{
    RenderWindow window(VideoMode(1280, 960), "Game", Style::Titlebar | Style::Close);
    window.setVerticalSyncEnabled(true);

    srand(time(NULL));
    Game game;
    Menu menu;
    Pause pause;
    

    while (window.isOpen())
    {
        Event ev;
        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
                window.close();
            else if (ev.type == Event::LostFocus)
            {
                multiplier = 0;
            }
            else if (ev.type == Event::GainedFocus)
            {
                multiplier = 1;
            }
        }

        //update
        if (runGame)
        {
            game.update(window);
            /*if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                if (goPause)
                {
                    pause.update(window);
                }
            }*/
        }
        else
        {
            menu.update(window);
        }
        window.clear();

        //render
        if (runGame)
        {
            game.render(window);
            /*if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                if (goPause)
                {
                    pause.render(window);
                }
            }*/
        }
        else
        {
            menu.render(window);
        }
        window.display();
    }
    return 0;
}