#ifndef _SYSTEM_H
#define  _SYSTEM_H
namespace ecs {
	class EntityManager;
	class System {
	public:
		System() = default;
		System(const System &) = delete;
		System(System &&) = delete;
		System& operator=(const System&) = delete;
		System& operator=(System&&) = delete;
		virtual ~System() = default;

		///<summary>Do the activity of the System.</summary>
		virtual void run(EntityManager &em) const = 0;
	};
};
#endif
