#include "tux.hpp"

#include <iostream>
#include <SDL/SDL.h>
#include <sstream>

#include "defines.hpp"
#include "exception.hpp"
#include "game.hpp"
#include "graphics.hpp"
#include "logger.hpp"

using namespace std;

class TuxContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact *contact);
    void EndContact(b2Contact *contact);
};

static TuxContactListener contactListener;

Tux::Tux(float x, float y) :
    Entity("Tux"),
    _jumping(false)
{
    position.set(x, y);

    _texture = getTexMgr()->getResource("Tux");

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

    getWorld()->SetContactListener(&contactListener);
}

void Tux::update(float dt)
{
    Uint8 *keys = SDL_GetKeyState(NULL);
    const float magnitude = 0.5;

    if (keys[SDLK_LEFT])
    {
        _body->ApplyLinearImpulse(b2Vec2(-magnitude, 0),
                                  _body->GetWorldCenter());
    }
    if (keys[SDLK_RIGHT])
    {
        _body->ApplyLinearImpulse(b2Vec2(magnitude, 0),
                                  _body->GetWorldCenter());
    }
    if (keys[SDLK_UP])// && !_body->IsAwake())
    {
        //cout << "Jump pressed!" << endl;
        _body->ApplyLinearImpulse(b2Vec2(0, magnitude * 2),
                                  _body->GetWorldCenter());
    }

    Entity::update(dt);
}

string Tux::toString()
{
    ostringstream ss;
    ss << "Tux<Name = '" << getName() << "', Position: "
       << position.toString() << ">";
    return ss.str();
}

void TuxContactListener::BeginContact(b2Contact *contact)
{
    // Check if fixture A was Tux
    void *bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData)
        static_cast<Tux *>(bodyUserData)->startContact();

    // Check if fixture B was Tux
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if (bodyUserData)
        static_cast<Tux *>(bodyUserData)->startContact();
}

void TuxContactListener::EndContact(b2Contact *contact)
{
    // Check if fixture A was Tux
    void *bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData)
        static_cast<Tux *>(bodyUserData)->endContact();

    // Check if fixture B was Tux
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if (bodyUserData)
        static_cast<Tux *>(bodyUserData)->endContact();
}
