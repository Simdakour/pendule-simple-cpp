#ifndef __SEGMENT_H_
#define __SEGMENT_H_
#include <SFML/Graphics.hpp>




#define GRAVITY {0.f, 9.81f}

struct Segment
{
private:
	float _angle = 0.f;
	float _len = 0.f;
	float _bob_mass = 10;

	sf::Vector2f base = { 0.f, 0.f };
	sf::Vector2f tool_position = { 0.f, 0.f };
	sf::Vector2f tool_velocity = { 0.f, 0.f };
	sf::Vector2f tool_acceleration = { 0.f, 0.f };
		
	sf::CircleShape base_anchor;
	sf::CircleShape tool_anchor;
	sf::Vertex  segment[2] = { base, tool_position };

public:
	void create(float x, float y, float angle, float len)
	{
		base = { x, y };
		_angle = angle;
		_len = len;
		tool_position = { x + len * sin(angle), y + len * cos(angle) };

		sf::Vertex tmp[2] = { base, tool_position };
		memcpy(segment, tmp, sizeof(tmp));

		base_anchor.setRadius(5.f);
		tool_anchor.setRadius(5.f);

		base_anchor.setPosition({ base.x - 5.f, base.y - 5.f });
		tool_anchor.setPosition({ tool_position.x - 5.f, tool_position.y - 5.f });
	};

	void update(float dt)
	{
		// update position with verlet integration
		sf::Vector2f tool_position_new = tool_position + (tool_velocity * dt) + (tool_acceleration * dt * dt * 0.5f);
		sf::Vector2f tool_acceleration_new = GRAVITY;
		sf::Vector2f tool_velocity_new = tool_velocity + (tool_acceleration + tool_acceleration_new) * (dt * 0.5f);

		tool_position = tool_position_new;
		tool_velocity = tool_velocity_new;
		tool_acceleration = tool_acceleration_new;

		_angle += dt;
		
		tool_position = { base.x + _len * sin(_angle), base.y + _len * cos(_angle) };
		tool_anchor.setPosition({(base.x + _len * sin(_angle) - 5.f), (base.y + _len * cos(_angle) - 5.f)});
		sf::Vertex tmp[2] = { base, tool_position };
		memcpy(segment, tmp, sizeof(tmp));
		
	}

	void model()
	{

	}

	void show(sf::RenderWindow* w)
	{
		w->draw(base_anchor);
		w->draw(tool_anchor);
		w->draw(segment, 2, sf::Lines);
	}

};

#endif // !__SEGMENT_H_

