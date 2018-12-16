#include "StorageManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>

namespace memecity::engine 
{
	bool StorageManager::save(const std::string& file_path, std::map<std::string, std::string>& content) const
	{
		try
		{
			std::ofstream output_stream(file_path);
			if (output_stream)
			{
				std::for_each(content.begin(), content.end(),
				              [&output_stream](const std::pair<std::string, std::string>& pair)
				              {
					              output_stream << "[" + pair.first + ", " + pair.second + "]" + "\n";
				              });
				output_stream.close();
			}
		}
		catch (std::exception& exception)
		{
			std::cout << exception.what() << "\n";
			return false;
		}

		return true;
	}
}