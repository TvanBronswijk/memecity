#ifndef _SERIALIZABLE_H
#define _SERIALIZABLE_H
#include <map>
#include <any>

namespace memecity::engine::serialization {
	using SerializeInfo = std::map<std::string, std::string>;
	class Serializable
	{
	public:
		virtual SerializeInfo to_map() const = 0;
		virtual void from_map(SerializeInfo map) = 0;

		Serializable() = default;
		Serializable(const Serializable &) = delete;
		Serializable(Serializable &&) = delete;
		Serializable& operator=(const Serializable&) = delete;
		Serializable& operator=(Serializable&&) = delete;
		virtual ~Serializable() = default;
	};
	/* example of how to use
	 * std::map<std::string, std::any> example_guy::to_map()
	{
		std::map<std::string, std::any> map;

		map["name"] = this->name;
		map["age"] = this->age;
		map["legCount"] = this->legCount;
		map["friends"] = this->friends;
		map["money"] = this->money;

		return map;
	}

	void example_guy::from_map(std::map<std::string, std::any> map)
	{
		this->name = std::any_cast<std::string>(map["name"]);
		this->age = std::any_cast<int>(map["age"]);
		this->legCount = std::any_cast<int>(map["legCount"]);
		this->friends = std::any_cast<bool>(map["friends"]);
		this->money = std::any_cast<float>(map["money"]);
	}
	 */
}

#endif
