#include "groundbox.hpp"

#include <iostream>
#include <sstream>

#include "defines.hpp"
#include "game.hpp"
#include "graphics.hpp"

using namespace std;

GroundBox::GroundBox() : Entity("GroundBox")
{
    const float width = SCREEN_WIDTH;
    const float height = 1;
    position.set(width / 2.f, height / 2.f);

    _texture = getTexMgr()->getResource("Ground");

    b2BodyDef bodyDef;
    bodyDef.position = position.tob2Vec2();
    _body = getWorld()->CreateBody(&bodyDef);
    _body->SetUserData(this);

    b2PolygonShape bodyShape;
    const float halfWidth = _texture->getWidth() / 2.f;
    const float halfHeight = _texture->getHeight() / 2.f;
    bodyShape.SetAsBox(halfWidth, halfHeight, b2Vec2(0, 0), 0);
    _body->CreateFixture(&bodyShape, 0);
}

string GroundBox::toString()
{
    ostringstream ss;
    ss << "Tux<Name = '" << getName() << "', Position: "
       << position.toString() << ">";
    return ss.str();
}
