#include <algorithm>
#include <array>
#include <queue>
#include <iostream>
#include <forward_list>
#include <fstream>
#include <ostream>

#include <boost/filesystem.hpp>

#include "config.h"

namespace manifest
{
	using namespace std;
	using namespace boost::filesystem;

	const array<path, 4> projDirs { { path("CVS"),
	                                  path(".git"),
	                                  path(".svn"),
	                                  path(".hg") } };

	bool is_project_directory (const path & p)
	{
		bool isproj = false;
		for (size_t i = 0; i < projDirs.size(); ++i) {
			isproj = exists(p / projDirs[i]);
			if (isproj) break;
		}

		return isproj;
	}

	path remove_base (const path &base, const path &p) {
		// Take the relative path from the base directory
		// Irritatingly there is no built-in method for this
		path tmp = p;
		path diff;

		while (!tmp.empty() && tmp != base) {
			diff = tmp.filename() / diff;
			tmp = tmp.parent_path();
		}

		return diff;
	}

	class manifest_printer {
	private:
		const path &base;
	public:
		manifest_printer(const path &base);
		int print (ostream &out);
	};

	manifest_printer::manifest_printer(const path &base) : base(base) {}

	int manifest_printer::print (ostream &out) {
		// Start with the empty relative path
		queue<path> frontier;
		frontier.push( this->base );

		int c = 0;

		// As long as the frontier is non-empty, keep searching
		while ( !frontier.empty() ) {
			path p = frontier.front();
			frontier.pop();

			if (exists(p)) {
				// For project directories, output and escape immediately
				if ( is_project_directory(p) ) {
					++c;
					out << ( remove_base(this->base, p).string() ) << endl;
				}
				else {
					// Add all children to the frontier
					directory_iterator end_it;
					for (directory_iterator it(p); it != end_it; ++it) {
						if ( is_directory(it->status()) ) {
							frontier.push(it->path());
						}
					}
				}
			}
		}

		return c;
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		std::cout << PACKAGE_STRING << " <" << PACKAGE_URL << ">" << std::endl;
		std::cout << "usage: " << argv[0] << " /path/to/directory" << std::endl;
		return 1;
	}
	boost::filesystem::path projDir(argv[1]);

	auto m = manifest::manifest_printer(projDir);
	m.print(std::cout);
	return 0;
}
