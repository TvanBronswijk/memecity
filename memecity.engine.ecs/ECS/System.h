#ifndef _SYSTEM_H
#define  _SYSTEM_H

namespace ecs {
	using system_typetoken = const char*;

	class EntityManager;
	class System {
	protected:
	public:
		System() = default;
		System(const System &) = delete;
		System(System &&) = delete;
		System& operator=(const System&) = delete;
		System& operator=(System&&) = delete;

		///<summary>Get a type token.</summary>
		virtual system_typetoken get_type_token() const = 0;

		///<summary>Do the activity of the System.</summary>
		virtual void run(EntityManager &em) const = 0;

		virtual ~System() = default;
	};
};




#endif
