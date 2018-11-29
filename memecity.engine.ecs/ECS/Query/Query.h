#ifndef _QUERY_H
#define  _QUERY_H
#include <algorithm>
#include <functional>
#include <vector>
namespace memecity::engine::ecs::query {
		template<class T>
		using Predicate = std::function<bool(T&)>;

		template<class T>
		class ComponentQuery {
		protected:
			std::vector<std::reference_wrapper<T>> _collection;
		public:

			ComponentQuery(std::vector<std::reference_wrapper<T>> collection) : _collection(collection) {}

			ComponentQuery<T> where(Predicate<T> predicate) const
			{
				std::vector<std::reference_wrapper<T>> result;
				std::copy_if(_collection.begin(), _collection.end(), std::back_inserter(result), predicate);
				return ComponentQuery<T>(result);
			}
			T* first(Predicate<T> predicate) const
			{
				auto it = std::find_if(_collection.begin(), _collection.end(), predicate);
				if (it != _collection.end())
					return *it;
				return nullptr;
			}

			T* first() const
			{
				if (_collection.empty()) {
					return nullptr;
				}
				return &_collection.front().get();
			}
			std::vector<std::reference_wrapper<T>> to_vector() const
			{			
				return _collection;
			}
			~ComponentQuery() = default;
		};
};
#endif
