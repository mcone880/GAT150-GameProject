#pragma once
#include "Component.h"

namespace MAC {
	class Renderer;
	class GraphicsComponent : public Component {
	public:
		virtual void Draw(Renderer* renderer) = 0;
	};
}