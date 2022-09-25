#include "cGameManager.h"

#include "cBall.h"
#include "cPalette.h"
#include "cWindow.h"

#include "utils.h"

#include <optional>

auto ResolvePaddleCollision(const auto hasPaddleCollided, const auto& closestPoint, const auto& ball, const auto& paddle) -> const std::optional<glm::fvec2> {
	if (hasPaddleCollided)
	{
		auto newDirectionNormal = glm::fvec2{};

		const auto isLeftPaddle = paddle.IsAI();
		const auto upperCornerNormal = isLeftPaddle ? glm::fvec2{ +1, +1 } : glm::fvec2{ -1, +1 };
		const auto lowerCornerNormal = isLeftPaddle ? glm::fvec2{ +1, -1 } : glm::fvec2{ +1, -1 };
		const auto upperCornerCheck = isLeftPaddle ? glm::fvec2{ paddle.Position().x + paddle.Size().x, paddle.Position().y } : glm::fvec2{ paddle.Position().x, paddle.Position().y };
		const auto lowerCornerCheck = isLeftPaddle ? glm::fvec2{ paddle.Position().x + paddle.Size().x, paddle.Position().y + paddle.Size().y } : glm::fvec2{ paddle.Position().x, paddle.Position().y + paddle.Size().y };
		const auto upperBorderCheck = isLeftPaddle ? glm::fvec2{ paddle.Position().x + paddle.Size().x, paddle.Position().y + paddle.Size().y } : glm::fvec2{ paddle.Position().x, paddle.Position().y + paddle.Size().y };

		// check whether the collision happened on the corner of the palette
		if (closestPoint == upperCornerCheck) { newDirectionNormal = upperCornerNormal; }
		else if (closestPoint == lowerCornerCheck) { newDirectionNormal = lowerCornerNormal; }
		else if (closestPoint.x > paddle.Position().x && closestPoint.x < paddle.Position().x + paddle.Size().x && closestPoint.y == paddle.Position().y) { newDirectionNormal = upperCornerNormal; }
		else if (closestPoint.x > paddle.Position().x && closestPoint.x < paddle.Position().x + paddle.Size().x && closestPoint.y == paddle.Position().y + paddle.Size().y) { newDirectionNormal = lowerCornerNormal; }
		else { newDirectionNormal = { +1, +0 }; }

		return glm::normalize(glm::reflect(ball.Direction(), newDirectionNormal));
	}

	return std::nullopt;
};

cGameManager::cGameManager(cWindow& gameWindow)
	: m_hGameWindow{ gameWindow }, m_hBall(*this),
	m_hLeftPalette(*this, SDL_Color{ 0xff, 0xff, 0xff, 0xff }, false),
	m_hRightPalette(*this, SDL_Color{ 0xff, 0xff, 0xff, 0xff }, true) {}

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
		m_hBall.Spin();
		m_bIsPlaying = true;
	}

#pragma region CHECK_AND_RESOLVE_COLLISIONS
	const auto& [leftPaddleHasCollided, leftPaddleClosestPoint] = collisions::CheckIntersectionCircleAndRectangle(m_hBall, m_hLeftPalette);
	const auto& [rightPaddleHasCollided, rightPaddleClosestPoint] = collisions::CheckIntersectionCircleAndRectangle(m_hBall, m_hRightPalette);

	if (const auto hitNormal = ResolvePaddleCollision(leftPaddleHasCollided, leftPaddleClosestPoint, m_hBall, m_hLeftPalette)) { m_hBall.Direction() = hitNormal.value(); }
	if (const auto hitNormal = ResolvePaddleCollision(rightPaddleHasCollided, rightPaddleClosestPoint, m_hBall, m_hRightPalette)) { m_hBall.Direction() = hitNormal.value(); }
#pragma endregion

	// Check if ball is outside lateral bounds
	const auto& [screenW, screenH] = m_hGameWindow.GetSize();
	if ((m_hBall.Position().x + m_hBall.Radius()) > screenW 
		|| (m_hBall.Position().x - m_hBall.Radius()) < 0)
	{
		m_hBall.Reset();
		m_hLeftPalette.Reset();
		m_hRightPalette.Reset();
		m_bIsPlaying = false;
	}
}
