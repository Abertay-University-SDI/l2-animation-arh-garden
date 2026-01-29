#include "Player.h"

Player::Player(Input* inputRef) {
	m_input = inputRef;

	setPosition({ 200, 200 });

	// animations
	m_walkUp.addFrame(sf::IntRect({ 256,0 }, m_spriteRes));
	m_walkUp.addFrame(sf::IntRect({ 320,0 }, m_spriteRes));
	m_walkUp.addFrame(sf::IntRect({ 384,0 }, m_spriteRes));
	m_walkUp.addFrame(sf::IntRect({ 448,0 }, m_spriteRes));
	m_walkUp.setFrameSpeed(m_animSpeed);

	m_walkUpRight.addFrame(sf::IntRect({ 0,  64 }, m_spriteRes));
	m_walkUpRight.addFrame(sf::IntRect({ 64, 64 }, m_spriteRes));
	m_walkUpRight.addFrame(sf::IntRect({ 128,64 }, m_spriteRes));
	m_walkUpRight.addFrame(sf::IntRect({ 192,64 }, m_spriteRes));
	m_walkUpRight.setFrameSpeed(m_animSpeed);

	m_walkRight.addFrame(sf::IntRect({ 256,64 }, m_spriteRes));
	m_walkRight.addFrame(sf::IntRect({ 320,64 }, m_spriteRes));
	m_walkRight.addFrame(sf::IntRect({ 384,64 }, m_spriteRes));
	m_walkRight.addFrame(sf::IntRect({ 448,64 }, m_spriteRes));
	m_walkRight.setFrameSpeed(m_animSpeed);

	m_walkDownRight.addFrame(sf::IntRect({ 0,  128 }, m_spriteRes));
	m_walkDownRight.addFrame(sf::IntRect({ 64, 128 }, m_spriteRes));
	m_walkDownRight.addFrame(sf::IntRect({ 128,128 }, m_spriteRes));
	m_walkDownRight.addFrame(sf::IntRect({ 192,128 }, m_spriteRes));
	m_walkDownRight.setFrameSpeed(m_animSpeed);

	m_walkDown.addFrame( sf::IntRect({ 0, 0 }, m_spriteRes) );
	m_walkDown.addFrame( sf::IntRect({ 64,0 }, m_spriteRes) );
	m_walkDown.setFrameSpeed(m_animSpeed);


	m_walkUpLeft = m_walkUpRight;
	m_walkUpLeft.setFlipped(true);
	m_walkUpLeft.setFrameSpeed(m_animSpeed);

	m_walkLeft = m_walkRight;
	m_walkLeft.setFlipped(true);
	m_walkLeft.setFrameSpeed(m_animSpeed);

	m_walkDownLeft = m_walkDownRight;
	m_walkDownLeft.setFlipped(true);
	m_walkDownLeft.setFrameSpeed(m_animSpeed);

	m_currentAnimation = &m_walkDown;
};

void Player::update(float dt) {
	m_currentAnimation->animate(dt);
	setTextureRect( m_currentAnimation->getCurrentFrame() );

	// for diagonal movement
	float diagonal_speed = m_speed * APPROX_ONE_OVER_ROOT_TWO * dt;
	float orthog_speed = m_speed * dt;	// orthogonal movement

	switch (m_direction)
	{
	case Direction::UP:
		move({ 0, -orthog_speed });
		m_currentAnimation = &m_walkUp;
		break;
	case Direction::UP_RIGHT:
		move({ diagonal_speed, -diagonal_speed });
		m_currentAnimation = &m_walkUpRight;
		break;
	case Direction::RIGHT:
		move({ orthog_speed,0 });
		m_currentAnimation = &m_walkRight;
		break;
	case Direction::DOWN_RIGHT:
		move({ diagonal_speed, diagonal_speed });
		m_currentAnimation = &m_walkDownRight;
		break;
	case Direction::DOWN:
		move({ 0, orthog_speed });
		m_currentAnimation = &m_walkDown;
		break;
	case Direction::DOWN_LEFT:
		move({ -diagonal_speed, diagonal_speed });
		m_currentAnimation = &m_walkDownLeft;
		break;
	case Direction::LEFT:
		move({ -orthog_speed,0 });
		m_currentAnimation = &m_walkLeft;
		break;
	case Direction::UP_LEFT:
		move({ -diagonal_speed, -diagonal_speed });
		m_currentAnimation = &m_walkUpLeft;
		break;
	}

	// decrement and check the input buffer.
	m_inputBuffer -= dt;
	if (m_inputBuffer > 0)
	{
		// not long enough has passed since the last input change, so don't handle input
		return;
	}
	// grab this to detect changes per frame for later
	Direction last_dir = m_direction;
};
void Player::handleInput(float dt) {

	// decrement and check the input buffer.
	m_inputBuffer -= dt;
	if (m_inputBuffer > 0)
	{
		// not long enough has passed since the last input change, so don't handle input
		return;
	}
	// grab this to detect changes per frame for later
	Direction last_dir = m_direction;

	// Set 8-directional movement based on WASD
	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP_LEFT;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN_LEFT;
		else
			m_direction = Direction::LEFT;
	}
	else if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP_RIGHT;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN_RIGHT;
		else
			m_direction = Direction::RIGHT;
	}
	else
	{
		if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP;
		else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN;
	}

	// set input buffer if needed, this makes diagonal movement easier
	if (m_direction != last_dir)
		m_inputBuffer = INPUT_BUFFER_LENGTH;
};