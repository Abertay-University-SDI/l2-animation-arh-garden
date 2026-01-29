#include "Level.h"

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	/*m_snake.setRadius(20);
	m_snake.setPosition({ 50, 50 });
	m_snake.setFillColor(sf::Color::Green);*/

	// sheep
	if (!m_tex_sheep.loadFromFile("gfx/sheep_sheet.png")) {
		std::cerr << "Image file could not be loaded. :(";
	}
	m_sheep.setTexture(&m_tex_sheep);
	m_sheep.setTextureRect(sf::IntRect({0,0}, {64,64}));
	m_sheep.setSize({ 64,64 });
}

// handle user input
void Level::handleInput(float dt)
{
	if (m_gameOver) return;

	m_sheep.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	if (m_gameOver) return;

	// check wall collision
	sf::Vector2f pos = m_sheep.getPosition();
	float radius = m_sheep.getCollisionBox().size.x;

	if (pos.x < 0 || pos.x + radius > m_window.getSize().x || pos.y < 0 || pos.y + radius > m_window.getSize().y)
	{
		m_gameOver = true;
		std::cout << "Game over";
	}

	// sheep
	m_sheep.update(dt);
}

// Render level
void Level::render()
{
	beginDraw();
	//m_window.draw(m_snake);
	m_window.draw(m_sheep);
	endDraw();
}

