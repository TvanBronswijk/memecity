#include "StorageManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <SDL.h>

namespace memecity::engine
{
	bool StorageManager::save(const std::string& file_path, serialization::SerializeInfo data) const
	{
		std::string text;

		try
		{
			std::for_each(data.begin(), data.end(),
				[&](const std::pair<std::string, std::string> pair)
			{
				text += pair.first + "=" + pair.second + "\n";
			});

		}
		catch (std::exception& exception)
		{
			std::cout << exception.what() << "\n";
			return false;
		}

		return save(file_path, text);
	}



	bool StorageManager::save(const std::string& file_path, const std::string& data) const
	{
		try
		{
			std::string full_path = SDL_GetBasePath();
			full_path += "\\" + file_path;

			std::string directory;
			const size_t last_slash_idx = full_path.rfind('\\');
			if (std::string::npos != last_slash_idx)
			{
				directory = full_path.substr(0, last_slash_idx);
			}

			if(!filesystem::exists(directory)){
				filesystem::create_directories(directory);
			}

			std::ofstream output_stream(full_path);
			if (output_stream)
			{
				output_stream << data;
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


	serialization::SerializeInfo StorageManager::load(const std::string& file_path) const
	{
		serialization::SerializeInfo result;

		try
		{
			std::string full_path = SDL_GetBasePath();
			full_path += "\\" + file_path;
			std::ifstream input_stream;
			input_stream.open(full_path);

			if (input_stream.is_open() && input_stream.good())
			{
				std::string line;
				while (std::getline(input_stream, line))
				{
					auto key = line.substr(0, line.find('='));
					const auto value = line.substr(line.find('=') + 1);
					result[key] = value;
				}

				input_stream.close();
			}
		}
		catch (std::exception& exception)
		{
			std::cout << exception.what() << "\n";
		}

		return result;
	}

	std::string StorageManager::load_string(const std::string& file_path) const
	{
		std::string result;

		try
		{
			std::string full_path = SDL_GetBasePath();
			full_path += "\\" + file_path;
			std::ifstream input_stream;
			input_stream.open(full_path);

			if (input_stream.is_open() && input_stream.good())
			{
				std::string line;
				while (std::getline(input_stream, line))
				{
					result += line + '\n';
				}

				input_stream.close();
			}
		}
		catch (std::exception& exception)
		{
			std::cout << exception.what() << "\n";
		}

		return result;
	}

	std::map<std::filesystem::directory_entry, std::string> StorageManager::load_files_from_directory(const std::string& file_path) const
	{
		std::map<std::filesystem::directory_entry, std::string> temp;
		for (const auto& entry : filesystem::directory_iterator(file_path))
		{
			temp.insert(std::pair<std::filesystem::directory_entry, std::string>(entry, load_string(entry.path().string())));
		}
		return temp;
	}
	std::vector<std::string> StorageManager::get_filenames_from_directory(const std::string & directory_path) const
	{
		std::vector<std::string> temp;
		std::string absolute_path = SDL_GetBasePath();
		absolute_path += directory_path;
		for (const auto& entry : filesystem::directory_iterator(absolute_path))
		{
			if (!filesystem::is_directory(entry.path())) {
				std::string file_path = entry.path().string();
				const std::size_t found = file_path.find_last_of("/\\");

				temp.push_back(file_path.substr(found + 1));
			}
		}

		return temp;
	}

	std::vector<std::string> StorageManager::get_foldernames_from_directory(const std::string & directory_path) const
	{
		std::vector<std::string> temp;
		std::string absolute_path = SDL_GetBasePath();
		absolute_path += directory_path;
		for (const auto& entry : filesystem::directory_iterator(absolute_path))
		{
			if (filesystem::is_directory(entry.path())) {
				std::string file_path = entry.path().string();
				const std::size_t found = file_path.find_last_of("/\\");

				temp.push_back(file_path.substr(found + 1));
			}
		}

		return temp;
	}
}
