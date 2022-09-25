#pragma once

#include <glm/gtx/vector_angle.hpp>

#include <SDL.h>

#include "cBall.h"
#include "cPalette.h"

namespace drawings {
	auto DrawCircle(SDL_Renderer& renderer, const float radius, const glm::vec2& screenPos, const SDL_Color& color) -> void;
	auto DrawRectangle(SDL_Renderer& renderer, const glm::vec2& screenPos, const glm::vec2& size, const SDL_Color& color) -> void;
}// namespace drawings

namespace collisions {
	auto CheckIntersectionCircleAndRectangle(const cBall& ball, const cPalette& palette) -> std::tuple<bool, glm::fvec2>;
}// namespace collisions