#pragma once

#include "PEngine/Core.h"

#include <string>
#include <sstream>
#include <functional>

namespace PE
{
	/* The moment the Event gets dispatched, it gets dealt with immediatly.*/
	enum class EventType
	{
		/* These events are implemented in their specified Header file */
		None = 0, WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		/* We assign these to Bits as we can multiple bits set and mask the catagories out to an event */
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
							   virtual EventType GetEventType() const override {return GetStaticType(); }\
							   virtual const char* GetName() const override {return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class PE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		/* Filters out certain events */
		inline bool IsInCategory(EventCategory a_category)
		{
			return GetCategoryFlags() & a_category;
		}

		/* Sees if an event has been handled */
		bool m_handled = false;
	};

	class EventDispatcher
	{
		/* This is a way for us to dispatch Events based on their type */
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		/* We recieve an event reference (no idea what the event is, it is just a random event )*/
		EventDispatcher(Event& a_event)
			: m_event(a_event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> a_func)
		{
			if (m_event.GetEventType() == T::GetStaticType())
			{
				m_event.m_handled = a_func(*(T*)&m_event);
				return true;
			}
			return false;
		}
	private:
		Event& m_event;
	};

	/* Exists for out logging library */
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}