#pragma once

#include "PEngine/Layer.h"

#include "PEngine/Events/ApplicationEvent.h"
#include "PEngine/Events/KeyEvent.h"
#include "PEngine/Events/MouseEvent.h"

namespace PE
{
	class PE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}