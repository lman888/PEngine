#pragma once

#include "PEngine/Core.h"
#include "Layer.h"

#include <vector>

namespace PE
{
	/* The Layer Stack is just a wrapper for the Layers */
	class PE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* a_layer);
		void PushOverlay(Layer* a_overlay);
		void PopLayer(Layer* a_layer);
		void PopOverlay(Layer* a_overlay);

		std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_layers.end(); }

	private:
		/* Every frame, this will be iterated over */
		std::vector<Layer*> m_layers;
		unsigned int m_layerInsertIndex = 0;
	};
}

