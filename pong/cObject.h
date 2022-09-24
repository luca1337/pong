#pragma once

#include <string_view>

#include <glm/vec2.hpp>

#include <SDL_pixels.h>

class cObject
{
public:
	cObject() = default;

	virtual auto Update() -> void = 0;
	virtual auto Render() -> void = 0;
	virtual auto Reset() -> void = 0;

protected:
	glm::vec2 m_vLocation = {};
	std::string name = {};
	SDL_Color m_sColor = {};
};