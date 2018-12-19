#ifndef _SERIALIZATION_FACADE_H
#define _SERIALIZATION_FACADE_H

#include <string>
#include <map>
#include <any>
#include "../../dependencies/json.hpp"
#include "Serializable.h"

namespace memecity::engine::serialization {
	class SerializationFacade
	{
	public:
		template<class T>
		std::string serialize(T object) const
		{
			static_assert(std::is_convertible<T, Serializable>::value, "This function can only construct concrete subclasses of Serializable");
			SerializeInfo map = object.serialize();
			nlohmann::json json;

			for (auto entry : map)
			{
				if (entry.second.type().name() == typeid(int).name())
				{
					auto val = std::any_cast<int>(entry.second);
					json[entry.first] = val;
				}
				else if (entry.second.type().name() == typeid(std::string).name())
				{
					auto val = std::any_cast<std::string>(entry.second);
					json[entry.first] = val;
				}
				else if (entry.second.type().name() == typeid(float).name())
				{
					auto val = std::any_cast<float>(entry.second);
					json[entry.first] = val;
				}
				else if (entry.second.type().name() == typeid(bool).name())
				{
					auto val = std::any_cast<bool>(entry.second);
					json[entry.first] = val;
				}
			}
			return json.dump();



		}



		template <class T>
		T deserialize(std::string json_string) const
		{
			static_assert(std::is_convertible<T, Serializable>::value, "This function can only construct concrete subclasses of Serializable");
			SerializeInfo map;
			auto json = nlohmann::json::parse(json_string);


			for (const auto& entry : json.items())
			{
				if (entry.value().is_number())
				{
					if (entry.value().is_number_float())
					{
						map[entry.key()] = float(entry.value());
					}
					else {
						map[entry.key()] = int(entry.value());
					}
				}
				else if (entry.value().is_string())
				{
					map[entry.key()] = std::string(entry.value());
				}
				else if (entry.value().is_boolean())
				{
					map[entry.key()] = bool(entry.value());
				}
			}
			T result;

			result.deserialize(map);
			return result;
		}

	};
}

#endif
