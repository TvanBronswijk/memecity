#ifndef _STORAGE_MANAGER_H
#define _STORAGE_MANAGER_H

#include <string>
#include <map>

namespace memecity::engine {

	class StorageManager
	{
		public:
			bool save(const std::string& file_path, std::map<std::string, std::string>& content) const;
	};

}
#endif
