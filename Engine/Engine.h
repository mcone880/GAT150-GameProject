#pragma once

//core
#include "Core/FileSystem.h"

//Framework
#include "Framework/EventSystem.h"
#include "Framework/System.h"

//Graphics
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"

//Math
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

#include <vector>
#include <variant>
#include <algorithm>
#include <memory>

//resource
#include "Resource/ResourceSystem.h"

//objects
#include "Object/Actor.h"
#include "Object/Scene.h"

namespace MAC {
	class Engine {
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw();

		template<typename T>
		T* Get();

	private:
		std::vector<std::unique_ptr<System>> systems;
	};

	template<typename T>
	inline T* Engine::Get()
	{
		for (auto& system : systems) {
			if (dynamic_cast<T*>(system.get())) return dynamic_cast<T*>(system.get());
		}
		return nullptr;
	}
}