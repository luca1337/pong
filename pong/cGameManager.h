#pragma once

#include "cBall.h"
#include "cPalette.h"

#include <memory>
#include <vector>
#include <array>

class cGameManager sealed
{
public:
	cGameManager(class cWindow& gameWindow);
	cGameManager(cGameManager&) = delete;
	cGameManager(cGameManager&&) = delete;
	cGameManager(const cGameManager&) = delete;
	cGameManager(const cGameManager&&) = delete;

public:
	auto Update() -> void;
	auto& GetGameWindow() const { return m_hGameWindow; }

private:

	auto UpdateGameLogic() -> void;

private:

	class cWindow& m_hGameWindow;

	cBall m_hBall;
	cPalette m_hLeftPalette;
	cPalette m_hRightPalette;

	//std::vector<cObject> m_vObjects = {};

	bool m_bIsPlaying = {};
};