#pragma once

#include "FontHacks.h"

namespace PortabilityLayer
{
	class RenderedFont;
	class HostFont;

	class FontRenderer
	{
	public:
		virtual RenderedFont *RenderFont(HostFont *font, int size, FontHacks fontHacks) = 0;

		static FontRenderer *GetInstance();
	};
}