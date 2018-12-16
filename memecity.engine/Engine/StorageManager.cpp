#include "StorageManager.h"
#include <fstream>
#include <algorithm>

namespace memecity::engine 
{
	bool StorageManager::save(const std::string& file_path, std::map<std::string, std::string>& content) const
	{
		try
		{
			std::ofstream output_stream(file_path);
			if (output_stream)
			{
				// TODO: Use a std::algorithm to increase performance
				for (auto pair : content)
				{
					output_stream << "[" + pair.first + ", " + pair.second + "]" + "\n";
				}

				output_stream.close();

				//std::for_each(content.begin(), content.end(), [&output_stream](std::pair<std::string, std::string>& pair)
				//	{ output_stream << "[" + pair.first + ", " + pair.second + "]"; });
				//output_stream.close();
			}
		}
		catch (std::exception& exception)
		{
			return false;
		}

		return true;
	}
}
