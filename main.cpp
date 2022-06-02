#include "lib/file_search.h"

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
	using std::cout;
	// Check wether the user provided a command-line arguument.
	if(argc != 2)
	{
		cout << "Usage " << argv[0] << " <file_name>\n";
		return 1;
	}
	fs::path name {argv[1]};
	bool found_flag = false;
	file_search("/home/ruslan/", name, std::ref(found_flag)); 
	return 0;
}
