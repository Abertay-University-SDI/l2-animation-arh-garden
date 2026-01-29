#include "Player.h"

Player::Player() {
	setPosition({ 200, 200 });

	// animations
	m_walkDown.addFrame( sf::IntRect({ 0,0 }, { 64,64 }) );
	m_walkDown.addFrame( sf::IntRect({ 64,0 }, { 64,64 }) );
	m_walkDown.setFrameSpeed(1.f / 3.f);

	m_currentAnimation = &m_walkDown;
};

void Player::update(float dt) {
	m_currentAnimation->animate(dt);
	setTextureRect( m_currentAnimation->getCurrentFrame() );
};
void Player::handleInput(float dt) {

};