#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Entity : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
    public:
        explicit Entity();
    protected:
        b2Body* m_body;
        virtual void update();
    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // ENTITY_H
