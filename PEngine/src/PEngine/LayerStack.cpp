#include "pepch.h"
#include "LayerStack.h"

namespace PE
{
	LayerStack::LayerStack()
	{
		m_layerInsert = m_layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
			delete layer;
	}

	/* This gets pushed into the first part of the list */
	void LayerStack::PushLayer(Layer* a_layer)
	{
		m_layerInsert = m_layers.emplace(m_layerInsert, a_layer);
	}

	void LayerStack::PushOverlay(Layer* a_overlay)
	{
		m_layers.emplace_back(a_overlay);
	}

	/* We always want to render overlays last */
	/* This get pushed into the second part of the list */
	void LayerStack::PopLayer(Layer* a_layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), a_layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
			m_layerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* a_overlay)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), a_overlay);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
		}
	}
}