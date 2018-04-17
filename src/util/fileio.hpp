#ifndef fileio_hpp
#define fileio_hpp

#include <string>
#include <fstream>
#include <sstream>


namespace util {
		
	std::string read_file(const std::string& filename)
	{
			// TODO: fixme
			std::fstream file;
			file.open(filename);
			std::stringstream str_stream;
			if (file.good()) {
				std::string line;
				while (getline(file, line, '\n')) {
					str_stream << line;
				}
			}
			//str_stream << file.rdbuf();
			file.close();
			return str_stream.str();
	}


}

#endif