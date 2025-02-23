#pragma once

#include "RE/Bethesda/IDEvent.h"

namespace RE
{
	class MouseMoveEvent : public IDEvent
	{
	public:
		// members
		float x;
		float y;
	};
	static_assert(sizeof(MouseMoveEvent) == 0x40);
}
