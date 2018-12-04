#ifndef _ENTITY_BUILDER_H
#define  _ENTITY_BUILDER_H
#include "..\EntityManager.h"
namespace memecity::engine::ecs::builder {
		struct EntityBuilder {
			EntityManager* em;
			Entity* entity;
			EntityBuilder(EntityManager& em) : em(&em), entity(nullptr) {};
			const EntityBuilder& create_entity() 
			{ 
				entity = &em->create_entity();
				return *this;
			}
			template<class T, class... Args>
			const EntityBuilder& with_component(Args&&... args) const
			{
				static_assert(std::is_convertible<T*, Component*>::value, "This function can only construct concrete subclasses of Component");
				static_assert(std::is_constructible<T, Entity&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
				if (entity == nullptr) throw - 1;
				em->create_component<T>(*entity, std::forward<Args>(args)...);
				return *this;
			}
			const Entity& get() const { return *entity; }
			~EntityBuilder() = default;
		};
};
#endif
