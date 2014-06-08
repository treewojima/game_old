#include "beastie.hpp"

#include <SDL/SDL.h>
#include <sstream>

#include "defines.hpp"
#include "exception.hpp"
#include "game.hpp"
#include "graphics.hpp"
#include "logger.hpp"

using namespace std;

Beastie::Beastie(float x, float y) : Entity("Beastie")
{
    position.set(x, y);

    _texture = getTexMgr()->getResource("Beastie");

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position.tob2Vec2();
    bodyDef.allowSleep = true;
    _body = getWorld()->CreateBody(&bodyDef);
    _body->SetUserData(this);

    b2PolygonShape bodyShape;
    const float halfWidth = _texture->getWidth() / 2.f;
    const float halfHeight = _texture->getHeight() / 2.f;
    bodyShape.SetAsBox(halfWidth, halfHeight, b2Vec2(0, 0), 0);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &bodyShape;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.3;
    _body->CreateFixture(&fixtureDef);
}

string Beastie::toString()
{
    ostringstream ss;
    ss << "Beastie<Name = '" << getName() << "', Position: "
       << position.toString() << ">";
    return ss.str();
}


