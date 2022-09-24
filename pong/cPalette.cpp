#include "cPalette.h"

#include "utils.h"
#include "cWindow.h"
#include "cGameManager.h"

#include <SDL.h>

cPalette::cPalette(class cGameManager& gameManager, const SDL_Color& color, const bool isAI)
	: m_hGameManager{ gameManager }, m_bIsAI{ isAI }
{
	m_sColor = { color };

	Reset();

	name = isAI ? "right" : "left";
}

auto cPalette::Update() -> void
{
	const auto& window = m_hGameManager.GetGameWindow();
	const auto& [width, height] = window.GetSize();

	const auto upKey = m_bIsAI ? SDL_SCANCODE_UP : SDL_SCANCODE_W;
	const auto downKey = m_bIsAI ? SDL_SCANCODE_DOWN : SDL_SCANCODE_S;

	const auto insideScreenYUpper = (Position().y > 0);
	const auto insideScreenYLower = (Position().y + Size().y) < height;

	// move paddles within bounds
	if (window.GetKey(upKey) && insideScreenYUpper) { m_vLocation.y -= 0.3f * m_hGameManager.GetGameWindow().GetDeltaTime(); }
	if (window.GetKey(downKey) && insideScreenYLower) { m_vLocation.y += 0.3f * m_hGameManager.GetGameWindow().GetDeltaTime(); }
}

auto cPalette::Render() -> void
{
	const auto nativeRenderer = reinterpret_cast<SDL_Renderer*>(m_hGameManager.GetGameWindow().GetSDLRendererHandle());
	drawings::DrawRectangle(*nativeRenderer, m_vLocation, m_vSize, { m_sColor.r, m_sColor.g, m_sColor.b, m_sColor.a });
}

auto cPalette::Reset() -> void
{
	const auto& [screenW, screenH] = m_hGameManager.GetGameWindow().GetSize();

	const auto aiLocation = glm::vec2{ (screenW - m_vSize.x) - 10, (screenH / 2) - (m_vSize.y / 2) };
	const auto playerLocation = glm::vec2{ 10, (screenH / 2) - (m_vSize.y / 2) };

	m_vLocation = m_bIsAI ? aiLocation : playerLocation;
}
