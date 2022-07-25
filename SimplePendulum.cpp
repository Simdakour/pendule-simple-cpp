#include "SimplePendulum.h"

// Constructors //

// With params
SimplePendulum::SimplePendulum(float x, float y, float len, float angle, sf::Color color)
{
	_angle = angle;
	_len = len;

	_base.x = x;
	_base.y = y;

	_bob_position.x = _base.x + _len * sin(_angle);
	_bob_position.y = _base.y + _len * cos(_angle);

	sf::Vertex _bar[2] = { _base, _bob_position };

	_color = color;
	
	_bob.setRadius(_bob_radius);
	_bob.setFillColor(_color);
	_bob.setPosition({ _bob_position.x - _bob_radius, _bob_position.y - _bob_radius});
};

// Destructor //

SimplePendulum::~SimplePendulum() {};

// Methods //

// Set the new calculated positions for each elements (bob and bar)
void SimplePendulum::SetNewPos(float new_angle)
{
	// update position
	_bob_position = { _base.x + _len * sin(new_angle), _base.y + _len * cos(new_angle) };
	_bob.setPosition({ (_base.x + _len * sin(new_angle) - _bob_radius), (_base.y + _len * cos(new_angle) - _bob_radius) });

	sf::Vertex tmp[2] = { _base, _bob_position };
	memcpy(_bar, tmp, sizeof(tmp));
}

// Update by the deltatime the pendulum
void SimplePendulum::UpdateVerlet(float dt)
{
	// Compute drag force and drag acceleration
	float drag_force = 0.5f * DRAG * (_angle_dot * abs(_angle_dot));
	float drag_acc = drag_force / _bob_mass;

	// Use Verlet integration formalism
	float new_angle = _angle + (_angle_dot * dt) + ((float)_angle_dot_dot * dt * dt * 0.5);
	float new_angle_dot_dot = (-(GRAVITY * sin(_angle)) / _len) - drag_acc;
	float new_angle_dot = _angle_dot + ((float)_angle_dot_dot + new_angle_dot_dot) * (dt * 0.5);

	// Set the new state
	_angle_dot_dot = new_angle_dot_dot;
	_angle_dot = new_angle_dot;
	_angle = new_angle;

	// Set the newly calculated states
	SetNewPos(_angle); 
}

void SimplePendulum::UpdateEuler(float dt)
{
	// Compute drag force and drag acceleration
	float drag_force = 0.5f * DRAG * (_angle_dot * abs(_angle_dot));
	float drag_acc = drag_force / _bob_mass;

	// Use Euler integration formalism
	float new_angle_dot_dot = (-(GRAVITY * sin(_angle)) / _len) - drag_acc;
	float new_angle_dot = _angle_dot + new_angle_dot_dot * dt;
	float new_angle = _angle + new_angle_dot * dt;

	// Set the new state
	_angle_dot_dot = new_angle_dot_dot;
	_angle_dot = new_angle_dot;
	_angle = new_angle;

	// Set the newly calculated states
	SetNewPos(_angle);
}

// Show the pendulum
void SimplePendulum::Show(sf::RenderWindow* window)
{
	window->draw(_bar, 2, sf::Lines);
	window->draw(_bob);
}



