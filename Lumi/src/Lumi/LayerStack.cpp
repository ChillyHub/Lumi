#include "pch.h"
#include "LayerStack.h"

namespace Lumi
{
	LayerStack::LayerStack()
	{
		
	}

	LayerStack::~LayerStack()
	{
		for (auto layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsert++, layer);
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsert, layer);

		if (it != m_Layers.begin() + m_LayerInsert)
		{
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsert, m_Layers.end(), overlay);

		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}
}