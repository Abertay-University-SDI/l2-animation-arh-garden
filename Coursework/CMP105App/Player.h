#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/Input.h"

class Player : public GameObject
{
private:
	// animation
	sf::Vector2i m_spriteRes = { 64,64 };
	float m_animSpeed = 1.f / 8.f;

	Animation* m_currentAnimation;
	Animation m_walkUp;
	Animation m_walkUpRight;
	Animation m_walkRight;
	Animation m_walkDownRight;
	Animation m_walkDown;

	Animation m_walkUpLeft;
	Animation m_walkLeft;
	Animation m_walkDownLeft;

	// input
	enum class Direction { UP, DOWN, LEFT, RIGHT, UP_RIGHT, DOWN_RIGHT, DOWN_LEFT, UP_LEFT, NONE };
	Direction m_direction = Direction::NONE;

	float m_speed = 300.0f;
	float m_inputBuffer = 0.f;

	const float INPUT_BUFFER_LENGTH = 0.2f;
	const float APPROX_ONE_OVER_ROOT_TWO = 0.70710678f;	// 1 / sqrt(2)

public:
	Player(Input* inputRef);

	void update(float dt);
	void handleInput(float dt);
};

