#ifndef _STORAGE_MANAGER_H
#define _STORAGE_MANAGER_H

#include <string>
#include <map>
#include <filesystem>
#include "Serialize.h"

namespace filesystem = std::filesystem;

namespace memecity::engine {

	class StorageManager
	{
	private:
		serialization::SerializationFacade* _serialization_facade;

	public:
		StorageManager(serialization::SerializationFacade& sf) 
			: _serialization_facade(&sf) {}

		bool save(const std::string& file_path, serialization::SerializeInfo data) const;
		bool save(const std::string& file_path, const std::string& data) const;
		serialization::SerializeInfo load(const std::string& file_path) const;
		std::string load_string(const std::string& file_path) const;
		std::map<std::filesystem::directory_entry, std::string> load_files_from_directory(const std::string& file_path) const;
	};

}
#endif
