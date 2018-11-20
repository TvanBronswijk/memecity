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

			template<class C>
			ComponentQuery(std::vector<std::unique_ptr<C>>& collection)
			{
				for (auto& element : collection) {
					_collection.emplace_back(std::ref(static_cast<T&>(*element)));
				}
			};

			ComponentQuery<T> where(Predicate<T> predicate) const
			{
				std::vector<std::reference_wrapper<T>> result;
				for (auto& c : _collection) {
					if (predicate(c)) {
						result.emplace_back(c);
					}
				}
				return ComponentQuery<T>(result);
			}
			T* first(Predicate<T> predicate) const
			{
				for (auto& c : _collection) {
					if (predicate(c)) {
						return &c.get();
					}
				}
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
