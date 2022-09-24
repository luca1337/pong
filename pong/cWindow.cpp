#include "cWindow.h"

#include <SDL.h>

#include <glm/common.hpp>
#include <glm/gtx/vector_angle.hpp>

static uint64_t start = 0;
static uint64_t end = 0;

cWindow::cWindow(const uint32_t width, const uint32_t height, const std::string_view title)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("Couldn't initialize SDL2: [%s]", SDL_GetError());
		return;
	}

	this->m_hWindowHandle = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0x000000);
	if (!this->m_hWindowHandle)
	{
		SDL_Log("Couldn't initialize SDL2 Window: [%s]", SDL_GetError());
		return;
	}

	this->m_hRendererHandle = SDL_CreateRenderer(reinterpret_cast<SDL_Window*>(this->m_hWindowHandle), -1, SDL_RENDERER_ACCELERATED);
	if (!this->m_hRendererHandle)
	{
		SDL_Log("Couldn't initialize SDL2 Renderer: [%s]", SDL_GetError());
		return;
	}

	start = SDL_GetPerformanceCounter();
	keys = SDL_GetKeyboardState(nullptr);

	m_bIsPresenting = true;
	m_iWidth = width;
	m_iHeight = height;
}

auto cWindow::FlushQueueEvents() -> void
{
	SDL_Event ev = {};
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
		{
			m_bIsPresenting = !m_bIsPresenting;
		}
	}

	// clear screen and add alpha blending
	const auto nativeRenderer = reinterpret_cast<SDL_Renderer*>(this->m_hRendererHandle);
	SDL_SetRenderDrawBlendMode(nativeRenderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(nativeRenderer, 0x0, 0x0, 0x0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(nativeRenderer);

	// manage delta
	end = start;
	start = SDL_GetPerformanceCounter();
	this->m_fDeltaTime = static_cast<float>((((start - end) * 1000) / (float)SDL_GetPerformanceFrequency()));
}

auto cWindow::Present() const -> void
{
	SDL_RenderPresent(reinterpret_cast<SDL_Renderer*>(this->m_hRendererHandle));
}