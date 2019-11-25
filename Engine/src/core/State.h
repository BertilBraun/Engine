#pragma once

#include "Time.h"

namespace Engine
{
	class StateBase {
	public:
		virtual void Update(TimeStamp dt) = 0;
		virtual void Render(TimeStamp dt) = 0;
	};

}