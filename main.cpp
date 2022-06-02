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
	thread_file_search(name, 8);
	return 0;
}
