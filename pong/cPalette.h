#pragma once

#include "cObject.h"

#include <SDL.h>

#include <glm/vec2.hpp>

class cPalette sealed : public cObject
{
public:
	cPalette(class cGameManager& gameManager, const SDL_Color& color, const bool isAI);

	virtual auto Update() -> void override;
	virtual auto Render() -> void override;
	virtual auto Reset() -> void override;
public:
	auto& Position() { return m_vLocation; }
	const auto& Position() const { return m_vLocation; }
	auto& Size() { return m_vSize; }
	auto& Size() const { return m_vSize; }
	auto IsAI() const { return m_bIsAI; }
private:
	class cGameManager& m_hGameManager;

	const glm::vec2 m_vSize = { 20.0f, 80.0f };
	bool m_bIsAI = {};
};