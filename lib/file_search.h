#ifndef FILE_SEARCH
#define FILE_SEARCH

#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>

void thread_file_search(std::filesystem::path const & name, size_t amount_thread);

#endif
