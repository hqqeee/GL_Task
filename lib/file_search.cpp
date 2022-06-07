#include "file_search.h"
namespace fs = std::filesystem;

static void file_search(fs::path const & init, fs::path const & name, bool & found_flag, std::vector<bool>::reference status);

/*
 *		thread_file_search creates $(amount_threads) threads that call file_search function which search file with $(name). 
 */

void thread_file_search(fs::path const & name, size_t const amount_thread)
{
	using namespace std;
	vector<thread> thr;
	vector<bool> thr_status; // vector with flags indicating that thread have terminated.
	bool found_flag = false; // Flag that indicates if the file is found
	auto iter = fs::directory_iterator(fs::path{"/"}, fs::directory_options::skip_permission_denied);
	for(auto i = fs::begin(iter); fs::begin(i) != fs::end(iter);)
	{
		auto subroot = *(i++);
		bool last_dir = (fs::begin(i) == fs::end(iter));
		if(found_flag)  // If the file is found wait until all thread have finished.
		{	
			for(auto &t : thr)
			{
				t.join();
			}
			break;
		}
		if(thr.size() < amount_thread) // If the number of threads is not equal to the required, create a new one.
		{
	//		cout << "Thread created" << thr.size() << "    " << subroot.path()  << endl;
			thr_status.emplace_back(true);
			thr.emplace_back(file_search, subroot, name, ref(found_flag), thr_status.back());
		}
		if(thr.size() == amount_thread || last_dir) // If the number of thread is equal to the required,
													// wait until one of them is done.
		{
			auto thr_iter = begin(thr);
			auto thr_status_iter = begin(thr_status);
			size_t i = 0;
			while(1)
			{
	//			cout << i << "  " << *thr_status_iter << endl;
				if(!(*(thr_status_iter)))			// If the thread has status false, join it,
													// remove its elements from vectors.
				{
					thr_iter -> join();
					thr_status.erase(thr_status_iter);
					thr.erase(thr_iter);
					break;
				}
				thr_status_iter++;
				thr_iter++;
				i++;
				if(i == thr.size())
				{
					i = 0;
					thr_iter = begin(thr);
					thr_status_iter = begin(thr_status);
				}
			}
		}
		if(!found_flag && last_dir)
		{
			for(auto &t : thr)
			{
				t.join();
			}
			if(!found_flag) cout << "File not found.\n";
		}
	}
}

static void file_search(fs::path const & init, fs::path const & name, bool & found_flag);

static void file_search(fs::path const & init, fs::path const & name, bool & found_flag, std::vector<bool>::reference status)
{
	file_search(init, name, std::ref(found_flag));
	// When all files in subroot are checked, change status.
	status = false;
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
				try
				{
					file_search(subdir, name, std::ref(found_flag));
				}
				catch(fs::filesystem_error const& ex)
				{
	//				std::cout << subdir << " throws an exception:\n" << ex.what() << "\nSkipped.\n";
				}
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

