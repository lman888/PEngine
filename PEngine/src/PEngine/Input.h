#pragma once

#include "PEngine/Core.h"

namespace PE
{

	class PE_API Input
	{
	public:

		inline static bool IsKeyPressed(int a_keyCode)
		{
			return s_instance->IsKeyPressedImpl(a_keyCode);
		}

		inline static bool IsMouseButtonPressed(int a_button)
		{
			return s_instance->IsMouseButtonPressedImpl(a_button);
		}

		inline static float GetMouseX()
		{
			return s_instance->GetMouseXImpl();
		}

		inline static float GetMouseY()
		{
			return s_instance->GetMouseYImpl();
		}

		inline static std::pair<float, float>GetMousePos()
		{
			return s_instance->GetMousePositionImpl();
		}

	protected:

		virtual bool IsKeyPressedImpl(int a_keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int a_button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:

		static Input* s_instance;

	};

}