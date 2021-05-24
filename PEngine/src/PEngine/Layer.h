#pragma once

#include "PEngine/Core.h"
#include "PEngine/Events/Event.h"

namespace PE
{
	/* Layers are intended to live throughout the lifetime of the application at this current time */
	class PE_API Layer
	{
	public:

		Layer(const std::string& a_name = "Layer");
		virtual ~Layer();

		/* When a Layer is pushed onto the Layer Stack */
		virtual void OnAttach() {}
		/* When a Layer is detached from the Layer Stack */
		virtual void OnDetach() {}
		/* When a Layer is updated */
		virtual void OnUpdate() {}
		/* When any ImGui Rendering occurs */
		virtual void OnImGuiRender() {}
		/* When an event gets sent to the layer, it gets recieved here */
		virtual void OnEvent(Event& a_event) {}

		inline const std::string& GetName() const { return m_debugName; }

	protected:
		std::string m_debugName;
	};
}