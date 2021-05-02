#pragma once

#include "PEngine/Input.h"

namespace PE
{
	class WindowsInput : public Input
	{
	protected:

		virtual bool IsKeyPressedImpl(int a_keyCode) override;

		virtual bool IsMouseButtonPressedImpl(int a_button) override;
		virtual std::pair<float, float>GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}