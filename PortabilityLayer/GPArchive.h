#pragma once

namespace PortabilityLayer
{
	class ResTypeID;

	struct GpArcResourceTypeTag
	{
		char m_id[13];

		static GpArcResourceTypeTag Encode(const ResTypeID &tag);
	};
}