#include <stdio.h>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

bool found = false;

static void file_search(fs::path const & init, fs::path const & name)
{
	if(exists(init) && is_directory(init))
	{
		for(auto const & entry : fs::directory_iterator(init, fs::directory_options::skip_permission_denied))
		{
			auto filename = entry.path().filename();
			if(fs::is_directory(entry.status()))
			{
	//			std::cout << "Searching in " << entry << std::endl;
				file_search(entry, name);
				if(found) return;
			}
			else if(fs::is_regular_file(entry.status()))
			{
				if(filename == name)
				{
					std::cout << fs::absolute(entry.path()).c_str() << std::endl;
					found = true;
				}
				//return fs::absolute(entry.path());
			}
		}
	}
}

fs::path non_rec_file_search(fs::path const & init, fs::path const & name)
{

}

int main(int argc, char *argv[])
{
	using std::cout;
	// Check wether the user provided a command-line arguument.
	if(argc != 2)
	{
		cout << "Usage " << argv[0] << " <file_name>\n";
		return 1;
	}
	fs::path dir {argv[1]};
	file_search("/home/ruslan/", dir); 
	return 0;
}
