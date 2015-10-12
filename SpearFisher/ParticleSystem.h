#include <SFML/Graphics.hpp>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

	ParticleSystem(unsigned int count) :
		m_particles(count),
		m_vertices(sf::Points, count),
		m_lifetime(sf::seconds(6)),
		m_emitter(0, 0)
	{
	}

	void setEmitter(sf::Vector2f position, sf::Vector2f velocity)
	{
		m_emitter = position;
		emitVel = velocity;
	}

	void update(sf::Time elapsed)
	{
		for (std::size_t i = 0; i < m_particles.size(); ++i)
		{
			// update the particle lifetime
			Particle& p = m_particles[i];
			p.lifetime -= elapsed;

			// if the particle is dead, respawn it
			if (p.lifetime <= sf::Time::Zero)
				resetParticle(i);

			// update the position of the corresponding vertex
			m_vertices[i].position += p.velocity * elapsed.asSeconds();

			// update the velocity of the vertex
			//p.velocity += p.acceleration * elapsed.asSeconds();

			// update the alpha (transparency) of the particle according to its lifetime
			float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
			m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
		}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// our particles don't use a texture
		states.texture = NULL;

		// draw the vertex array
		target.draw(m_vertices, states);
	}

private:

	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
		sf::Vector2f acceleration;
	};

	void resetParticle(std::size_t index)
	{
		// give a random velocity and lifetime to the particle
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 30) + 15.f;

		//float acceleration = (std::rand() % 10) + 10.f;
		//float angle2 = angle -= 3.14f / 2;

		m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed) + sf::Vector2f(emitVel.x * 1, emitVel.y * 1);
		m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

		//m_particles[index].acceleration = sf::Vector2f(std::cos(angle2) * acceleration, std::sin(angle) * acceleration);
		m_particles[index].acceleration = sf::Vector2f(0, 100);

		// reset the position of the corresponding vertex
		m_vertices[index].position = m_emitter;
	}

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;
	sf::Vector2f emitVel;
};

