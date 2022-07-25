#ifndef __SIMPLE_PENDULUM_H
#define __SIMPLE_PENDULUM_H
#include <SFML/Graphics.hpp>
#include <math.h>

constexpr float PI = 3.14159265358979323846f;
constexpr float GRAVITY = 9.81f;
constexpr float DRAG = 0.5f;

class SimplePendulum
{
private:
	float _angle = PI / 2;
	float _angle_dot = 0.f;
	float _angle_dot_dot = 0.f;
	float _len = 10.f;
	float _bob_mass = 1.f;
	float _bob_radius = 25.f;

	sf::Color _color;

	sf::Vector2<float> _base{ 0.0f, 0.0f };
	sf::Vector2<float> _bob_position{ _base.x + _len * sin(_angle), _base.y + _len * cos(_angle) };

	sf::CircleShape _bob;
	sf::Vertex _bar[2] = {_base, _bob_position};

	void SetNewPos(float new_angle);

public:
	SimplePendulum(float x, float y, float len, float angle, sf::Color color);
	~SimplePendulum();

	void UpdateVerlet(float dt);
	void UpdateEuler(float dt);
	void Show(sf::RenderWindow* window);
};

#endif // !__SIMPLE_PENDULUM_H

