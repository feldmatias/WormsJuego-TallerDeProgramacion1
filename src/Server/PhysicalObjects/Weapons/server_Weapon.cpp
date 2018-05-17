#include "Weapon.h"
#include "b2Fixture.h"
#include "b2CircleShape.h"
#include "CollisionData.h"
#include "Worm.h"
#include "math_utils.h"

int Weapon::weapon_id = 1;

#include <iostream>////////////////////////////////////////////////////////////////////////////////////////

Weapon::Weapon(World& world, GameParameters& parameters, int damage, int radius): 
	PhysicalObject(world, Weapon::weapon_id++, TYPE_WEAPON), parameters(parameters), 
	damage(damage), radius(radius), 
	waiting_to_explode(false), time_to_explode(-1), explode_time(world, *this){}

Weapon::~Weapon(){
	this->explode_time.join();
}

bool Weapon::isActive(){
	return this->waiting_to_explode || PhysicalObject::isActive();
}

void Weapon::shoot(char dir, int angle, int power, int time){
	if (dir == -1){
		angle = 180 - angle;
	}
	this->time_to_explode = time;
	this->angle = angle;
	this->power = power;
	std::cout<<"weapon shoot"<<std::endl;
}

void Weapon::shoot(Worm& shooter, b2Vec2 pos){}

void Weapon::getBodyDef(b2BodyDef& body_def, const b2Vec2& pos){
	body_def.type = b2_dynamicBody;
	body_def.position.Set(pos.x, pos.y);
	body_def.fixedRotation = true;
}

void Weapon::createFixtures(){
	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0); //position, relative to body position
	circleShape.m_radius = weapon_size / 2; //radius
		  
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 4;
	this->body->CreateFixture(&fixtureDef);
}

void Weapon::setInitialVelocity(){
	if (this->angle < 500){
		int velocity = this->parameters.getWeaponsVelocity();
		if (this->power != -1){
			 velocity *= this->power / 1000;
		}
		b2Vec2 linear_velocity(velocity * Math::cos_degrees(this->angle), velocity * Math::sin_degrees(this->angle));
		this->body->SetLinearVelocity(linear_velocity);
	}
	this->waiting_to_explode = true;
	this->explode_time.setTime(this->time_to_explode);
	this->explode_time.start();
}


void Weapon::explode(){
	std::cout<<"weapon explode: "<<this->getId()<<std::endl;
	b2Vec2 center = this->body->GetPosition();
	for (float bullet_angle = 0; bullet_angle < 360; bullet_angle+= 5){
		this->attackWormExplosion(center, bullet_angle);
	}
	
	this->explode_time.stop();
	this->waiting_to_explode = false;
	this->is_dead = true;
}

void Weapon::attackWormExplosion(const b2Vec2& center, int angle){
	b2Vec2 end = center + this->radius * b2Vec2(Math::cos_degrees(angle), Math::sin_degrees(angle));
	b2Vec2 normal;
	b2Body* closest_body = this->world.getClosestObject(center, end, normal);
	if (closest_body){
		CollisionData* data = (CollisionData*)closest_body->GetUserData();
		if (data->getType() == TYPE_WORM){
			Worm* worm = ((Worm*)data->getObject());
			float distance = b2Distance(center, worm->getPosition());
			int worm_damage = this->damage * (1 - distance / (2 * this->radius)); //Justo en el borde hace la mitad de danio
			worm->receive_weapon_damage(worm_damage, normal, this->id);
		}
	}
}

void Weapon::collide_with_something(CollisionData* other){
	std::cout<<"weapon collision"<<std::endl;
	if (this->time_to_explode == -1 || other->getType() == TYPE_BORDER){
		this->explode_time.stop();
		this->explode();
	}
}
