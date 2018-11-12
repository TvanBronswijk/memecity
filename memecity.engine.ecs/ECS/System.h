#ifndef _SYSTEM_H
#define  _SYSTEM_H
namespace ecs {
	class EntityManager;
	class System {	
	public:
		const enum Scope { draw, update };

		System() = default;
		System(const System &) = delete;
		System(System &&) = delete;
		System& operator=(const System&) = delete;
		System& operator=(System&&) = delete;
		virtual ~System() = default;

		///<summary>Run the System.</summary>
		virtual void run(EntityManager &em) const = 0;
	};
};
#endif
