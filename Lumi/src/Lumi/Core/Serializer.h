#pragma once

#include "pch.h"

#include "Lumi/Scene/Scene.h"
#include "Lumi/Scene/Component/Component.h"
#include "Lumi/Scene/Component/Transform.h"
#include "Lumi/Scene/Component/Camera.h"
#include "Lumi/Scene/Component/Material2D.h"
#include "Lumi/Scene/Component/Script.h"

#include <yaml-cpp/yaml.h>

namespace Lumi
{
	class Entity;

	class Serializer
	{
	public:
		Serializer() = default;

		template <typename T>
		inline void Serialize(T* src, const std::string& filepath);

		template <typename T>
		inline void SerializeRuntime(T* src, const std::string& filepath);

		template <typename T>
		inline bool Deserialize(T* dst, const std::string& filepath);

		template <typename T>
		inline bool DeserializeRuntime(T* dst, const std::string& filepath);
	private:
		void SerializeEntity(YAML::Emitter& out, Entity* entity);
	};
}