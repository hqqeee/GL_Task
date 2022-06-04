#include "file_search.h"

namespace fs = std::filesystem;

static void file_search(fs::path const & init, fs::path const & name, bool & found_flag);

/*
 *		thread_file_search creates $(amount_threads) threads that call file_search function which search file with $(name). 
 */
void thread_file_search(fs::path const & name, size_t amount_thread)
{
	using namespace std;
	vector<thread> thr;
	bool found_flag = false; // Flag that indicates if the file is found
	auto iter = fs::directory_iterator(fs::path{"/"}, fs::directory_options::skip_permission_denied);
	for(auto i = fs::begin(iter); fs::begin(i) != fs::end(iter);)
	{
		auto subroot = *(i++);
		bool last_dir = (fs::begin(i) == fs::end(iter));
		// skip_dir: boolean that indicates dir which we need to skip. These dirs can cause filesystem errors, 
		// like "too many level of symbolic links" etc.
		bool skip_dir = (subroot.path() == "/run" || subroot.path() == "/tmp" || subroot.path() == "/proc" || subroot.path() == "/snap" 
				 || subroot.path() == "/root" || subroot.path() == "/sys");
		if(found_flag) break;
		if(thr.size() < amount_thread && !skip_dir)
		{
		//	cout << "Thread created" << thr.size() << "    " << subroot.path()  << endl;
			thr.emplace_back(file_search, subroot, name, ref(found_flag));
		}
		if(thr.size() == amount_thread || last_dir)
		{	
			for(auto &t : thr) // wait until all threads are done.
			{
				t.join();
			//	cout << "finished " << endl;
			}
			thr.clear();
		}
	}
}

/*
 *	Recursive file search algorithm. args: init - initial path, name - filename to search, found_flag - indicates if the file was found.
 *  If file was found its print it.
 */

static void file_search(fs::path const & init, fs::path const & name, bool & found_flag)
{
	for(auto const & subdir : fs::directory_iterator(init, fs::directory_options::skip_permission_denied))
	{
		if(fs::exists(subdir))
		{
			if(fs::is_directory(subdir.status()))
			{
	//			std::cout << "Searching in " << subdir << std::endl;
				file_search(subdir, name, std::ref(found_flag));
				if(found_flag)
				{
					return;
				}
			}
			else if(fs::is_regular_file(subdir.status()))
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
}

