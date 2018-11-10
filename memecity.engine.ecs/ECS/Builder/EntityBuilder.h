#ifndef _ENTITY_BUILDER_H
#define  _ENTITY_BUILDER_H
#include "..\EntityManager.h"
namespace ecs {
	namespace builder {
		struct EntityBuilder {
			EntityManager& em;
			const Entity& entity;
			EntityBuilder(EntityManager& em) : em(em), entity(em.create_entity()) {};
			template<class T, class... Args>
			EntityBuilder& add_component(Args&&... args) 
			{
				em.create_component<T>(entity, std::forward<Args>(args)...);
				return *this;
			}
			const Entity& build() { return entity; }
			~EntityBuilder() = default;
		};
	}

};
#endif
