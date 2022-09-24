#include "utils.h"

namespace drawings {
	auto DrawCircle(SDL_Renderer& renderer, const float radius, const glm::vec2& screenPos, const SDL_Color& color) -> void
	{
		for (auto angle = 0ul; angle != (2 * glm::degrees(glm::two_pi<float>())); ++angle)
		{
			const auto cosTheta = (radius * static_cast<float>(glm::cos(angle)));
			const auto sinTheta = (radius * static_cast<float>(glm::sin(angle)));

			SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
			SDL_RenderDrawPoint(&renderer, static_cast<int>((screenPos.x + cosTheta)), static_cast<int>((screenPos.y + sinTheta)));
		}
	}

	auto DrawRectangle(SDL_Renderer& renderer, const glm::vec2& screenPos, const glm::vec2& size, const SDL_Color& color) -> void
	{
		const auto rect = SDL_FRect{
			.x = screenPos.x,
			.y = screenPos.y,
			.w = size.x,
			.h = size.y
		};

		SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawRectF(&renderer, &rect);
	}
}// namespace drawings

namespace collisions {
	auto CheckIntersectionCircleAndRectangle(const cBall& ball, const cPalette& palette) -> bool
	{
		const auto closestX = glm::clamp(ball.Position().x, palette.Position().x, palette.Position().x + palette.Size().x);
		const auto closestY = glm::clamp(ball.Position().y, palette.Position().y, palette.Position().y + palette.Size().y);

		const auto distX = (ball.Position().x - closestX);
		const auto distY = (ball.Position().y - closestY);

		return (glm::pow(distX, 2) + glm::pow(distY, 2)) <= glm::pow(ball.Radius(), 2);
	}
}// namespace collisions

