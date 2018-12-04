#include "Enemy.h"
#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include <random>

void Enemy::setBody(float32 x, float32 y, float32 radius, b2World& world) {
	b2BodyDef bodyDef;
	bodyDef.allowSleep = false;
	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;
	bodyDef.fixedRotation = true;
	bodyDef.position.x = x;
	bodyDef.position.y = y;
	bodyDef.linearDamping = 0.0f;
	bodyDef.userData = static_cast<RigidBody*>(this);
	b2CircleShape shape;
	shape.m_p.Set(0.0f, 0.0f);
	shape.m_radius = radius;
	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.1f;
	fixtureDef.filter.categoryBits = 0b0000'0000'0000'0010'0000;
	fixtureDef.filter.maskBits = 0b0000'0000'0000'0000'1111;
	fixtureDef.friction = 0.0f;
	//fixtureDef.isSensor = false;
	fixtureDef.restitution = 1.0f;
	fixtureDef.shape = &shape;
	_body = world.CreateBody(&bodyDef);
	setUp(shape, fixtureDef);
}

Enemy::Enemy(){
	
}

Enemy::Enemy(float32 x, float32 y, float32 width, float32 height, float32 maxSpeed, float32 halfLife, 
	float32 changeProbability, float32 framerate,Texture *texture)
	: ArkanoidObject(x,y,width,height,texture), _speed(maxSpeed), _halfLife(halfLife), 
	_changeProbability(changeProbability), _timer(new b2Timer()), _animationTimer(new b2Timer()),_framerate(framerate), _frame(0) {
	setBody(x, y, width / 2.0f, *Game::getWorld());
	float32 ra = rand() / (RAND_MAX + 1.)*M_PI * 2;
	setVelocity(b2Vec2{ sin(ra)*_speed, cos(ra)*_speed });
	_timer->Reset();
	_animationTimer->Reset();
}

Enemy::~Enemy(){
	delete _timer;
	delete _animationTimer;
}

void Enemy::update(){
	if (_timer->GetMilliseconds() > _halfLife*1000.0f) {
		if (rand() / (RAND_MAX + 1.) <= _changeProbability) {
			float32 ra = rand() / (RAND_MAX + 1.)*M_PI * 2;
			setVelocity(b2Vec2{ sin(ra)*_speed, cos(ra)*_speed });
		}
		_timer->Reset();
	}
	if (_animationTimer->GetMilliseconds() > 1000.0f / _framerate) {
		if ((++_frame) > _texture->getNumCols()*_texture->getNumRows()) {
			_frame = 0;
		}
		_animationTimer->Reset();
	}
	
}

void Enemy::onBeginContact(RigidBody* rigidBody) {
	if (dynamic_cast<Ball*>(rigidBody)||dynamic_cast<Paddle*>(rigidBody)) {
		destroy();
		Game::gameManager()->addScore(50);
	}
}

void Enemy::render() const{
	b2Vec2 pos = _body->GetPosition();

	_texture->renderFrame({ (int)pos.x - (int)getSize().x / 2, (int)pos.y - (int)getSize().y / 2,
		(int)_fixture->GetShape()->m_radius * 2, (int)_fixture->GetShape()->m_radius * 2 }, 
		 _frame/(_texture->getNumCols()+1), _frame%_texture->getNumCols());
}

std::istream& Enemy::deserialize(std::istream& out){
	return out;
}

std::ostream& Enemy::serialize(std::ostream& is) const{
	return is;
}