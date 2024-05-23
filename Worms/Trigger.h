#pragma once
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <functional>

class Trigger
{
public:
	Trigger( b2Fixture*, std::function<void( b2Contact )> );
private:
};

