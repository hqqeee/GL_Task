#include "lib/file_search.h"
#include <string>

namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
	using std::cout;
	// Check wether the user provided a command-line arguument.
	if(argc != 2 && argc != 3)
	{
		cout << "Usage " << argv[0] << " <file_name> <thread_amount>";
		return 1;
	}
	fs::path name {argv[1]};
	int thread_amount = 3;
	if(std::stoi(argv[2]) >= 3 && std::stoi(argv[2]) <= 8 )
	{
		thread_amount = std::stoi(argv[2]);
	}
	else 
	{
		cout << "Wrong number of threads. Default: 3.";
	}
	thread_file_search(name, thread_amount);
	return 0;
}
