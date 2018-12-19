#ifndef _STORAGE_MANAGER_H
#define _STORAGE_MANAGER_H

#include <string>
#include <map>
#include "Serialize.h"

namespace memecity::engine {

	class StorageManager
	{
	private:
		serialization::SerializationFacade* _serialization_facade;

	public:
		StorageManager(serialization::SerializationFacade& sf) 
			: _serialization_facade(&sf) {}

		bool save(const std::string& file_path, serialization::SerializeInfo data) const;
		bool save_string(const std::string& file_path, std::string data) const;
		serialization::SerializeInfo load(const std::string& file_path) const;
		std::string load_string(const std::string& file_path) const;
	};

}
#endif
