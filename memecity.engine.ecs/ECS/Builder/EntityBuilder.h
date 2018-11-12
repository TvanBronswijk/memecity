#ifndef _ENTITY_BUILDER_H
#define  _ENTITY_BUILDER_H
#include "..\EntityManager.h"
namespace memecity::engine::ecs::builder {
		struct EntityBuilder {
			EntityManager& em;
			Entity* entity;
			EntityBuilder(EntityManager& em) : em(em), entity(nullptr) {};
			const EntityBuilder& create_entity() 
			{ 
				entity = &em.create_entity();
				return *this;
			}
			template<class T, class... Args>
			const EntityBuilder& with_component(Args&&... args) const
			{
				if (entity == nullptr) throw - 1;
				entity->add<T>(em.create_component<T>(*entity, std::forward<Args>(args)...));
				return *this;
			}
			const Entity& get() const { return *entity; }
			~EntityBuilder() = default;
		};
};
#endif
