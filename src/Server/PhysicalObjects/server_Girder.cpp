#include "Girder.h"
#include "b2PolygonShape.h"
#include "b2Fixture.h"

Girder::Girder(World& world, size_t size): PhysicalObject(world, 0, "Girder"), size(size){}

Girder::~Girder(){}

void Girder::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_staticBody; 
	body_def.position.Set(pos.x, pos.y); 
}

void Girder::createFixtures(){
	b2PolygonShape boxShape;
	boxShape.SetAsBox(this->size / 2.0, 0.4);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	this->body->CreateFixture(&boxFixtureDef);
}