#ifndef _ECS_QUERY_H
#define _ECS_QUERY_H
#include <algorithm>
#include <memory>
#include <vector>



namespace memecity::engine::ecs {
	template<class T>
	class Query {
		using Predicate = std::function<bool(T&)>;
	private:
		friend class EntityManager;
		std::vector<std::reference_wrapper<T>> _collection;
		Query(std::vector<std::reference_wrapper<T>> collection) : _collection(collection) {}
	public:
		~Query() = default;
		Query<T> where(Predicate predicate) const {
			std::vector<std::reference_wrapper<T>> result;
			std::copy_if(_collection.begin(), _collection.end(), std::back_inserter(result), predicate);
			return Query<T>(result);
		}
		T* first(Predicate predicate) const {
			auto it = std::find_if(_collection.begin(), _collection.end(), predicate);
			if (it != _collection.end())
				return &((*it).get());
			return nullptr;
		}
		T* first() const {
			if (_collection.empty()) {
				return nullptr;
			}
			return &_collection.front().get();
		}
		std::vector<std::reference_wrapper<T>> to_vector() const { return _collection; }
	};
}

#endif
