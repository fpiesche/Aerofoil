#include "MacFileInfo.h"
#include "PLBigEndian.h"

#include <string.h>

namespace PortabilityLayer
{
	
	static const unsigned int kOffsetFileType = 0;
	static const unsigned int kOffsetFileCreator = 4;
	static const unsigned int kOffsetXPos = 8;
	static const unsigned int kOffsetYPos = 10;
	static const unsigned int kOffsetFinderFlags = 12;
	static const unsigned int kProtected = 14;
	static const unsigned int kCreationDate = 15;
	static const unsigned int kModifiedDate = 19;

	static const unsigned int kSize = 23;

	uint8_t m_data[kSize];

	void MacFilePropertiesSerialized::Deserialize(MacFileProperties &props) const
	{
		memcpy(props.m_fileType, m_data + kOffsetFileType, 4);
		memcpy(props.m_fileCreator, m_data + kOffsetFileCreator, 4);
		memcpy(&props.m_xPos, m_data + kOffsetXPos, 2);
		memcpy(&props.m_yPos, m_data + kOffsetYPos, 2);
		memcpy(&props.m_finderFlags, m_data + kOffsetFinderFlags, 2);
		memcpy(&props.m_protected, m_data + kProtected, 1);
		memcpy(&props.m_creationDate, m_data + kCreationDate, 4);
		memcpy(&props.m_modifiedDate, m_data + kModifiedDate, 4);

		PortabilityLayer::ByteSwap::BigInt16(props.m_xPos);
		PortabilityLayer::ByteSwap::BigInt16(props.m_yPos);
		PortabilityLayer::ByteSwap::BigUInt16(props.m_finderFlags);
		PortabilityLayer::ByteSwap::BigUInt32(props.m_creationDate);
		PortabilityLayer::ByteSwap::BigUInt32(props.m_modifiedDate);
	}

	void MacFilePropertiesSerialized::Serialize(const MacFileProperties &props)
	{
		int16_t xPos = props.m_xPos;
		int16_t yPos = props.m_yPos;
		uint16_t finderFlags = props.m_finderFlags;
		uint32_t creationDate = props.m_creationDate;
		uint32_t modifiedDate = props.m_modifiedDate;

		PortabilityLayer::ByteSwap::BigInt16(xPos);
		PortabilityLayer::ByteSwap::BigInt16(yPos);
		PortabilityLayer::ByteSwap::BigUInt16(finderFlags);
		PortabilityLayer::ByteSwap::BigUInt32(creationDate);
		PortabilityLayer::ByteSwap::BigUInt32(modifiedDate);

		memcpy(m_data + kOffsetFileType, props.m_fileType, 4);
		memcpy(m_data + kOffsetFileCreator, props.m_fileCreator, 4);
		memcpy(m_data + kOffsetXPos, &xPos, 2);
		memcpy(m_data + kOffsetYPos, &yPos, 2);
		memcpy(m_data + kOffsetFinderFlags, &finderFlags, 2);
		memcpy(m_data + kProtected, &props.m_protected, 1);
		memcpy(m_data + kCreationDate, &creationDate, 4);
		memcpy(m_data + kModifiedDate, &modifiedDate, 4);
	}
}