#include "pch.h"

#include "Serializer.h"
#include "Lumi/Scene/Entity.h"

namespace YAML 
{
	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::quat>
	{
		static Node encode(const glm::quat& rhs)
		{
			Node node;
			node.push_back(rhs.w);
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::quat& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.w = node[0].as<float>();
			rhs.x = node[1].as<float>();
			rhs.y = node[2].as<float>();
			rhs.z = node[3].as<float>();
			return true;
		}
	};
}

namespace Lumi
{
	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::quat& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.w << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}
	
	template <>
	void Serializer::Serialize(Scene* scene, const std::string& filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << scene->Name;
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		scene->GetRegistry().view<Transform>().each([&](auto entityID, Transform& trans)
			{
				auto entity = trans.entity;
				if (!entity) return;

				SerializeEntity(out, entity);
			});
		out << YAML::EndSeq;
		out << YAML::EndMap;

		//out << YAML::BeginMap;
		//out << YAML::Key << "EditorScene" << YAML::Value << "EditorScene";
		//out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
		//scene->GetRegistry().view<Transform>().each([&](auto entityID, Transform& trans)
		//	{
		//		auto entity = trans.entity;
		//		if (!entity) return;
		//
		//		SerializeEntity(out, entity);
		//	});
		//out << YAML::EndSeq;
		//out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	template <>
	void Serializer::SerializeRuntime(Scene* src, const std::string& filepath)
	{
		LUMI_CORE_ASSERT(false, "");
	}

	template <>
	bool Serializer::Deserialize(Scene* scene, const std::string& filepath)
	{
		YAML::Node data;
		try
		{
			data = YAML::LoadFile(filepath);
		}
		catch (const std::exception& e)
		{
			LUMI_CORE_ERROR("Load file fialed: {0}", e.what());
			return false;
		}

		if (!data["Scene"])
		{
			return false;
		}

		try
		{
			std::string sceneName = data["Scene"].as<std::string>();
			scene->Name = sceneName;
			LUMI_CORE_TRACE("Deserialized scene: {0}", sceneName);

			auto entities = data["Entities"];
			if (entities)
			{
				for (auto entity : entities)
				{
					unsigned int uuid = entity["Entity"].as<unsigned int>();

					std::string name = entity["Name"].as<std::string>();
					LUMI_CORE_TRACE("Deserialized entity: {0}, {1}",
						(unsigned int)uuid, name);

					Entity newEnt = scene->CreateEntity(name);

					auto transform = entity["Transform"];
					if (transform)
					{
						auto& trans = newEnt.GetComponent<Transform>();
						trans.Position = transform["Position"].as<glm::vec3>();
						trans.Rotation = transform["Rotation"].as<glm::quat>();
						trans.Scale = transform["Scale"].as<glm::vec3>();
					}

					auto camera = entity["Camera"];
					if (camera)
					{
						auto& cam = newEnt.AddComponent<Camera>();
						cam.Activated = camera["Acrivated"].as<bool>();
						cam.Aspect = camera["Aspect"].as<float>();
						cam.FarClip = camera["FarClip"].as<float>();
						cam.MovementSpeed = camera["MovementSpeed"].as<float>();
						cam.NearClip = camera["NearClip"].as<float>();
						cam.Projection = (ProjectionType)camera["Peojection"].as<int>();
						cam.ScreenHeight = camera["ScreenHeight"].as<float>();
						cam.ScreenWidth = camera["ScreenHeight"].as<float>();
						cam.Size = camera["Size"].as<float>();
						cam.Zoom = camera["Zoom"].as<float>();
					}

					auto material = entity["Material2D"];
					if (material)
					{
						auto& mat = newEnt.AddComponent<Material2D>();
						mat.QuadColor = material["Color"].as<glm::vec4>();
						mat.Texture2D = nullptr;
					}

					auto script = entity["Script"];
					if (script)
					{
						auto& scp = newEnt.AddComponent<Script>();
						scp.Activated = script["Activated"].as<bool>();
					}
				}
			}
		}
		catch (const std::exception& e)
		{
			LUMI_CORE_ERROR("Deserialize file fialed: {0}", e.what());
			return false;
		}
		
		return true;
	}

	template <>
	bool Serializer::DeserializeRuntime(Scene* dst, const std::string& filepath)
	{
		LUMI_CORE_ASSERT(false, "");
		return false;
	}

	void Serializer::SerializeEntity(YAML::Emitter& out, Entity* entity)
	{
		out << YAML::BeginMap;

		out << YAML::Key << "Entity" << YAML::Value << entity->GetEntityID();

		out << YAML::Key << "Name" << YAML::Value << entity->Name;

		auto& transform = entity->GetComponent<Transform>();
		out << YAML::Key << "Transform";
		out << YAML::BeginMap;
		out << YAML::Key << "Position" << YAML::Value << transform.Position;
		out << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
		out << YAML::Key << "Scale" << YAML::Value << transform.Scale;
		out << YAML::EndMap;

		if (entity->HasComponent<Camera>())
		{
			auto& camera = entity->GetComponent<Camera>();
			
			out << YAML::Key << "Camera";
			out << YAML::BeginMap;
			out << YAML::Key << "Activated" << YAML::Value << camera.Activated;
			out << YAML::Key << "Aspect" << YAML::Value << camera.Aspect;
			out << YAML::Key << "FarClip" << YAML::Value << camera.FarClip;
			out << YAML::Key << "MovementSpeed" << YAML::Value << camera.MovementSpeed;
			out << YAML::Key << "NearClip" << YAML::Value << camera.NearClip;
			out << YAML::Key << "Projection" << YAML::Value << (int)camera.Projection;
			out << YAML::Key << "ScreenHeight" << YAML::Value << camera.ScreenHeight;
			out << YAML::Key << "ScreenWidth" << YAML::Value << camera.ScreenWidth;
			out << YAML::Key << "Size" << YAML::Value << camera.Size;
			out << YAML::Key << "Zoom" << YAML::Value << camera.Zoom;
			out << YAML::EndMap;
		}

		if (entity->HasComponent<Material2D>())
		{
			auto& material = entity->GetComponent<Material2D>();

			out << YAML::Key << "Material2D";
			out << YAML::BeginMap;
			out << YAML::Key << "Color" << material.QuadColor;
			//out << YAML::Key << "Texture2D" << material.Texture2D;
			out << YAML::EndMap;
		}

		if (entity->HasComponent<Script>())
		{
			auto& script = entity->GetComponent<Script>();

			out << YAML::Key << "Script";
			out << YAML::BeginMap;
			out << YAML::Key << "Activated" << script.Activated;
			out << YAML::EndMap;
		}

		out << YAML::EndMap;
	}
}