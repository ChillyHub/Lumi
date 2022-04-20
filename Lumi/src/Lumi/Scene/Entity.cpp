#include "pch.h"

#include "Entity.h"

namespace Lumi
{
	Entity::Entity(const Entity& src)
		: transform(src.transform)
	{
		Name = src.Name;
		m_Entity = src.m_Entity;
		m_Scene = src.m_Scene;
	}
}