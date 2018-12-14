#ifndef _RW_OPS_WRAPPER_H
#define _RW_OPS_WRAPPER_H
#include <algorithm>
#include <fstream>

namespace memecity::engine::sdl {


	class FileWrapper
	{
	private:
		std::string _file_name;
		std::fstream _file_stream;
		std::string _buffer;

	public:

		FileWrapper(const char* file_name)
			: _file_name(file_name) {}

		~FileWrapper()
		{
			if (_file_stream.is_open())
			{
				_file_stream.close();
			}
		}

		const std::string read_file()
		{
			_file_stream = std::fstream(_file_name);
			if (_file_stream.is_open() && _file_stream.good())
			{
				while (std::getline(_file_stream, _buffer))
				{

				}
				_file_stream.close();
			}

			return _buffer;
		}

		void write(const std::string& content)
		{
			_file_stream = std::fstream(_file_name);

			if (_file_stream.is_open())
			{
				_file_stream << content;
			}
			_file_stream.close();
		}

		int get_lines()
		{
			return std::count(std::istreambuf_iterator<char>(_file_stream),
				std::istreambuf_iterator<char>(), '\n');
		}
	};
}
#endif