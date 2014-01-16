#include "Projectile.h"

#include "Category.h"
#include "Utility.h"

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Projectile::Projectile(Type type, const TextureHolder& textures, b2World& world, int damage): Entity(),
    m_type(type),
    m_sprite(textures.get(Textures::Bullet)),
    m_damage(damage)
{
    sf::Rect<float> spriteBounds = m_sprite.getGlobalBounds();
    setOrigin(sf::Vector2f(spriteBounds.width/2,spriteBounds.height/2));

    b2BodyDef ProjectileBodyDef;
    ProjectileBodyDef.type = b2_dynamicBody;
    ProjectileBodyDef.bullet = true;
    m_body = world.CreateBody(&ProjectileBodyDef);

    b2FixtureDef ProjectileFixtureDef;
    b2PolygonShape ProjectileShape;
    ProjectileShape.SetAsBox((spriteBounds.width/2.0f)/SCALE, (spriteBounds.height/2.0f)/SCALE);
    ProjectileFixtureDef.shape = &ProjectileShape;
    ProjectileFixtureDef.density = 1.0f;
    ProjectileFixtureDef.restitution = 0.1f;
    ProjectileFixtureDef.friction = 0.0f;
    ProjectileFixtureDef.userData = this;
    m_body->CreateFixture(&ProjectileFixtureDef);
}

unsigned int Projectile::getCategory() const
{
    return Category::AlliedProjectile;
}

int Projectile::getDamage() const
{
    return m_damage;
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    Entity::updateCurrent(dt,commands);
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_sprite, states);
}