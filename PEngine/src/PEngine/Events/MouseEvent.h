#pragma once

#include "Event.h"

#include <sstream>

namespace PE
{
	class PE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float a_x, float a_y)
			: m_mouseX(a_x), m_mouseY(a_y) {}

		inline float GetX() const { return m_mouseX; }
		inline float GetY() const { return m_mouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_mouseX, m_mouseY;
	};

	class PE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float a_xOffSet, float a_yOffSet)
			: m_xOffSet(a_xOffSet), m_yOffSet(a_yOffSet) {}

		inline float GetXOffSet() const { return m_xOffSet; }
		inline float GetYOffSet() const { return m_yOffSet; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolled: " << GetXOffSet() << ", " << GetYOffSet();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_xOffSet, m_yOffSet;

	};

	class PE_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:
		MouseButtonEvent(int a_button)
			: m_button(a_button) {}

		int m_button;
	};

	class PE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int a_button)
			: MouseButtonEvent(a_button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class PE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int a_button)
			: MouseButtonEvent(a_button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}