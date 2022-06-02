#ifndef FILE_SEARCH
#define FILE_SEARCH

#include <iostream>
#include <filesystem>
#include <thread>
#include <vector>

void file_search(std::filesystem::path const & init, std::filesystem::path const & name, bool & found_flag);

#endif
