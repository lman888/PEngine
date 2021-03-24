#pragma once

#include "Core.h"

namespace PE
{
	class PE_API App
	{
	public:
		App();

		void Run();
	};

	/* To be defined in Client */
	App* CreateApp();
}