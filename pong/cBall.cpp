#include "cBall.h"

#include "utils.h"
#include "cWindow.h"

#include "cGameManager.h"

cBall::cBall(cGameManager& gameManager) : cObject{}, m_hGameManager { gameManager }, m_vCurrentDirection{ 0, 0 } 
{
	m_vLocation = { 450, 400 };
	name = "ball";
	m_sColor = { 0xff, 0xff, 0xff, 0xff };
}

auto cBall::Update() -> void
{
	constexpr auto ballSpeed = 0.27f;

	const auto& [screenW, screenH] = m_hGameManager.GetGameWindow().GetSize();

	// Check ball boundaries
	if ((m_vLocation.y + m_fRadius) >= screenH) { m_vCurrentDirection	= glm::reflect<glm::vec2>(m_vCurrentDirection, { 0, -1 }); }	// bottom
	if ((m_vLocation.y - m_fRadius) <= 0.0f) { m_vCurrentDirection		= glm::reflect<glm::vec2>(m_vCurrentDirection, { 0, 1 }); }	// top

	// update position
	m_vLocation += (m_vCurrentDirection * ballSpeed) * m_hGameManager.GetGameWindow().GetDeltaTime();
}

auto cBall::Render() -> void
{
	const auto nativeRenderer = reinterpret_cast<SDL_Renderer*>(m_hGameManager.GetGameWindow().GetSDLRendererHandle());
	drawings::DrawCircle(*nativeRenderer, m_fRadius, m_vLocation, m_sColor);
}

auto cBall::Reset() -> void
{
	m_vLocation = { 450, 400 };
	m_vCurrentDirection = { 0, 0 };
}

auto cBall::RandomSpin() -> void
{
	const auto randomDirections = std::vector<glm::vec2>{
		{-1.0f, -1.0f},
		{+1.0f, -1.0f},
		{+1.0f, +1.0f},
		{-1.0f, +1.0f},
	};

	m_vCurrentDirection = randomDirections[rand() % randomDirections.size()];
}
