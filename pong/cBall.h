#pragma once

#include "cObject.h"

#include <glm/vec2.hpp>

class cBall sealed : public cObject
{
	enum class BallDirection {
		None = 0,
		NorthWest,
		NorthEast,
		SouthEast,
		SouthWest,
		EnumMax = SouthWest + 1
	};
public:
	cBall(class cGameManager& gameManager);

	virtual auto Update() -> void override;
	virtual auto Render() -> void override;
	virtual auto Reset() -> void override;

public:
	auto& Direction() { return m_vCurrentDirection; }
	auto& Position() { return m_vLocation; }
	const auto& Position() const { return m_vLocation; }
	auto Radius() const { return m_fRadius; }
	auto RandomSpin() -> void;

private:
	class cGameManager& m_hGameManager;

	BallDirection m_eStartDirection = {};
	glm::vec2 m_vCurrentDirection = {};

	const float m_fRadius = 15.0f;
};