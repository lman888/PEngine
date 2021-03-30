#pragma once

#include "Event.h"

#include <sstream>

namespace PE
{
	class PE_API KeyEvent : public Event
	{
	protected:

		KeyEvent(int a_keyCode)
			: m_keyCode(a_keyCode) {}

		int m_keyCode;

	public:
		inline int GetKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	};

	class PE_API KeyPressedEvent : public KeyEvent
	{
	private:
		int m_repeatCount;

	public:
		KeyPressedEvent(int a_keyCode, int a_repeatCount)
			: KeyEvent(a_keyCode), m_repeatCount(a_repeatCount) {}

		inline int GetRepeatCount() const { return m_repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class PE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int a_keyCode)
			: KeyEvent(a_keyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};
}