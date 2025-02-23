#pragma once

#include "RE/Bethesda/BS/BSFixedString.h"

#include <cstdint>

namespace RE
{
	enum class INPUT_DEVICE : std::uint8_t
	{
		None     = static_cast<std::uint8_t>(-1),
		Keyboard = 0,
		Mouse,
		Gamepad,
		VirtualKeyboard,

		TOTAL
	};

	enum class INPUT_EVENT_TYPE : std::uint32_t
	{
		Button        = 0,
		MouseMove     = 1,
		CursorMove    = 2,
		Char          = 3,
		Thumbstick    = 4,
		DeviceConnect = 5,
		DeviceChange  = 6,
	};

	class InputEvent
	{
	public:
		virtual ~InputEvent();

		virtual bool                   HasIDCode() const;
		virtual const BSFixedStringCS& QUserEvent() const;

		// members
		INPUT_DEVICE     device;     // 08
		std::uint8_t     pad09;      // 09
		std::uint16_t    pad0A;      // 0A
		std::int32_t     deviceId;   // 0C
		INPUT_EVENT_TYPE eventType;  // 10
		std::uint32_t    pad14;      // 14
		InputEvent*      next;       // 18
		std::int32_t     queueIndex; // 20
		std::int32_t     handled;    // 24
	};
	static_assert(sizeof(InputEvent) == 0x28);
}
