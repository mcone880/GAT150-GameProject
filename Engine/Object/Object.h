#pragma once

namespace MAC {

	class Object {
	public:
		virtual ~Object() {}

		virtual void Create() {}
	};
}