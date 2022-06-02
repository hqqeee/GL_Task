#include "file_search.h"

namespace fs = std::filesystem;

void file_search(fs::path const & init, fs::path const & name, bool & found_flag)
{
	for(auto const & subdir : fs::directory_iterator(init, fs::directory_options::skip_permission_denied))
	{
		if(fs::is_directory(subdir.status()))
		{
			file_search(subdir, name, std::ref(found_flag));
			if(found_flag)
			{
				return;
			}
		}
		else
		{
			auto filename{subdir.path().filename()};
			if(filename == name)
			{
				std::cout << fs::absolute(subdir.path()).c_str() << std::endl;
				found_flag = true;
			}
		}
	}
}

