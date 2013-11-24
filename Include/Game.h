#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <list>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "World.h"
#include "Player.h"

class Game : private sf::NonCopyable
{
    public:
        explicit Game();
        void run();

    private:
        void processInputs();
        void update(sf::Time elapsedTime);
        void updateStatistics(sf::Time elapsedTime);
        void render();

    private:
        sf::RenderWindow m_window;

        World m_world;
        Player m_player;

        sf::Text m_statisticsText;
        sf::Font m_font;
        sf::Time m_statisticsUpdateTime;
		std::size_t	m_statisticsNumFrames;
};

#endif // GAME_H