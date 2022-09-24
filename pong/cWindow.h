#pragma once

#include <tuple>
#include <string_view>

#include <SDL_types.h>

struct sWindowData {
	uint32_t width;
	uint32_t height;
};

class cWindow sealed
{
public:
	cWindow(const uint32_t width, const uint32_t height, const std::string_view title);
	cWindow(cWindow&) = delete;
	cWindow(cWindow&&) = delete;
	cWindow(const cWindow&) = delete;
	cWindow(const cWindow&&) = delete;

public:
	auto FlushQueueEvents() -> void;
	auto Present() const -> void;

public:
	[[ nodiscard ]] const auto GetSize() const { return std::make_tuple(m_iWidth, m_iHeight); }
	const auto GetDeltaTime() const { return m_fDeltaTime; }
	const auto IsPresenting() const { return m_bIsPresenting; }
	const auto GetSDLWindowHandle() const { return m_hWindowHandle; }
	const auto GetSDLRendererHandle() const { return m_hRendererHandle; }
	const auto GetKey(auto key) const { return keys[key] != 0; };

private:
	void* m_hWindowHandle = {};
	void* m_hRendererHandle = {};

	uint32_t m_iWidth = {};
	uint32_t m_iHeight = {};

	float m_fDeltaTime = {};

	bool m_bIsPresenting = {};

	const Uint8* keys = {};
};