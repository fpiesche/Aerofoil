#pragma once

#include "RGBAColor.h"

namespace PortabilityLayer
{
	class StandardPalette
	{
	public:
		static const unsigned int kSize = 256;

		StandardPalette();

		const RGBAColor *GetColors() const;
		static uint8_t MapColorAnalyticTruncated(unsigned int r, unsigned int g, unsigned int b);
		static uint8_t MapColorAnalytic(uint8_t r, uint8_t g, uint8_t b);
		static uint8_t MapColorAnalytic(const RGBAColor &color);
		uint8_t MapColorLUT(uint8_t r, uint8_t g, uint8_t b) const;
		uint8_t MapColorLUT(const RGBAColor &color) const;

		static const StandardPalette *GetInstance();

	private:
		static StandardPalette ms_instance;

		RGBAColor m_colors[kSize];
		uint8_t m_lut[16 * 16 * 16];
	};
}