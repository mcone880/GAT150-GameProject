#pragma once
#include "Framework/System.h"
#include "Resource.h"
#include <string>
#include <map>
#include <memory>
#include <algorithm>

namespace MAC {

	class ResourceSystem : public System{
	public:
		void Startup() override {}
		void Shutdown() override {}
		void Update(float dt) override {}

		void Add(const std::string& name, std::shared_ptr<MAC::Resource> resource);

		template<typename T>
		std::shared_ptr<T> Get(const std::string& name, void* data = nullptr);

	private:
		std::map<std::string, std::shared_ptr<Resource>> resources;
	};

	template<typename T>
	inline std::shared_ptr<T> ResourceSystem::Get(const std::string& name, void* data)
	{
		if (resources.find(String_ToLower(name)) != resources.end()) {
			return std::dynamic_pointer_cast<T>(resources[String_ToLower(name)]);
		}
		else {
			std::shared_ptr resource = std::make_shared<T>();
			resource->Load(name, data);
			resources[String_ToLower(name)] = resource;

			return resource;
		}
	}

	inline void ResourceSystem::Add(const std::string& name, std::shared_ptr<MAC::Resource> resource) {
		resources[String_ToLower(name)] = resource;
	}
}