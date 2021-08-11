#pragma once

//Audio
#include "Audio/AudioSystem.h"

//core
#include "Core/FileSystem.h"
#include "Core/Timer.h"
#include "Core/Utilities.h"

//Framework
#include "Framework/EventSystem.h"
#include "Framework/System.h"

//Graphics
#include "Graphics/Renderer.h"
#include "Graphics/Texture.h"
#include "Graphics/ParticleSystem.h"
#include "Graphics/Font.h"

//Math
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Random.h"
#include "Math/MathUtils.h"
#include "Math/Transform.h"

//STD
#include <vector>
#include <algorithm>
#include <memory>

//Input
#include "Input/InputSystem.h"

//resource
#include "Resource/ResourceSystem.h"

//objects
#include "Object/Actor.h"
#include "Object/Object.h"
#include "Object/Scene.h"

namespace MAC {
	class Engine {
	public:
		void Startup();
		void Shutdown();

		void Update();
		void Draw(Renderer* renderer);

		template<typename T>
		T* Get();

	public:
		FrameTimer time;

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