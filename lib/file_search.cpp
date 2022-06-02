#include "file_search.h"

namespace fs = std::filesystem;

static void file_search(fs::path const & init, fs::path const & name, bool & found_flag, std::vector<bool>::reference thread_flag);

void thread_file_search(fs::path const & name, size_t amount_thread)
{
	using namespace std;
	vector<thread> thr;
	vector<bool> thr_status;
	bool found_flag = false;
	for(auto const & subroot : fs::directory_iterator(fs::path{"/"}))
	{
		if(subroot.path() == "/run" || subroot.path() == "/tmp") continue;
		if(thr.size() < amount_thread)
		{
			cout << "Thread number: " << thr.size() << " created " << endl;
			thr_status.emplace_back(true);
			thr.emplace_back(file_search, subroot, name, ref(found_flag), thr_status.back());
		}
		else
		{
		
			for(auto &t : thr)
			{
				t.join();
			}
		/*
		while(1)
		{
			for(size_t i = 0; i < amount_thread; i++)
				{
					if(!thr_status[i])
					{
						cout << "HERE";
						thr[i].join();
						break;
					}
				}
		}*/
		}
		}
}

static void file_search(fs::path const & init, fs::path const & name, bool & found_flag);

static void file_search(fs::path const & init, fs::path const & name, bool & found_flag, std::vector<bool>::reference thread_flag)
{
	file_search(init, name, std::ref(found_flag));
	thread_flag = false;
}

static void file_search(fs::path const & init, fs::path const & name, bool & found_flag)
{
	for(auto const & subdir : fs::directory_iterator(init, fs::directory_options::skip_permission_denied))
	{
		if(fs::exists(subdir))
		{
			if(fs::is_directory(subdir.status()))
			{
				std::cout << "Searching in " << subdir << std::endl;
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

