#ifndef _QUERY_H
#define  _QUERY_H
#include <algorithm>
#include <functional>
#include <vector>
namespace ecs {
	namespace query {
		template<class T>
		class Query {
		protected:
			std::vector<std::reference_wrapper<T>> _collection;
		public:

			Query(std::vector<std::reference_wrapper<T>> collection) : _collection(collection) {}

			template<class C>
			Query(std::vector<std::unique_ptr<C>>& collection)
			{
				for (auto& element : collection)
					_collection.emplace_back(std::ref(static_cast<T&>(*element)));
			};

			Query<T> where(std::function<bool(T&)> predicate) const
			{
				std::vector<std::reference_wrapper<T>> result;
				for (auto& c : _collection)
					if (predicate(c))
						result.emplace_back(c);
				return Query<T>(result);
			}
			T* first(std::function<bool(T&)> predicate) const
			{
				for (auto& c : _collection)
					if (predicate(c))
						return &c.get();
				return nullptr;
			}

			T* first() const
			{
				if (_collection.empty())
					return nullptr;
				return &_collection.front().get();
			}
			std::vector<std::reference_wrapper<T>> to_vector() const
			{			
				return _collection;
			}
			~Query() = default;
		};
	}
};
#endif
