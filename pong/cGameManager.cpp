#include "cGameManager.h"

#include "cBall.h"
#include "cPalette.h"
#include "cWindow.h"

#include "utils.h"

cGameManager::cGameManager(cWindow& gameWindow)
	: m_hGameWindow{ gameWindow }, m_hBall(*this),
	m_hLeftPalette(*this, SDL_Color{ 0x0, 0xff, 0x0, 0xff }, false),
	m_hRightPalette(*this, SDL_Color{ 0xff, 0x0, 0x0, 0xff }, true) {}

auto cGameManager::Update() -> void
{
	while (m_hGameWindow.IsPresenting())
	{
		// flush command queue
		m_hGameWindow.FlushQueueEvents();

		// Update pong ball and palettes

		m_hBall.Update();
		m_hBall.Render();

		m_hLeftPalette.Update();
		m_hLeftPalette.Render();

		m_hRightPalette.Update();
		m_hRightPalette.Render();

		// draw and update objects here..
		UpdateGameLogic();

		// present to screen
		m_hGameWindow.Present();
	}
}

auto cGameManager::UpdateGameLogic() -> void
{
	if (m_hGameWindow.GetKey(SDL_SCANCODE_SPACE) && !m_bIsPlaying)
	{
		m_hBall.RandomSpin();
		m_bIsPlaying = true;
	}

	const auto beginCollisionWithLeftPaddle = collisions::CheckIntersectionCircleAndRectangle(m_hBall, m_hLeftPalette);
	const auto beginCollisionWithRightPaddle = collisions::CheckIntersectionCircleAndRectangle(m_hBall, m_hRightPalette);

	if (beginCollisionWithLeftPaddle) { m_hBall.Direction() = glm::reflect(m_hBall.Direction(), glm::vec2{ +1, 0 }); }
	if (beginCollisionWithRightPaddle) { m_hBall.Direction() = glm::reflect(m_hBall.Direction(), glm::vec2{ -1, 0 }); }

	// Check if ball is outside lateral bounds
	const auto& [screenW, screenH] = m_hGameWindow.GetSize();

	if (m_hBall.Position().x + m_hBall.Radius() > screenW) { m_hBall.Reset(); m_hLeftPalette.Reset(); m_hRightPalette.Reset(); m_bIsPlaying = false; }
	if (m_hBall.Position().x - m_hBall.Radius() < 0) { m_hBall.Reset(); m_hLeftPalette.Reset(); m_hRightPalette.Reset(); m_bIsPlaying = false; }
}
