#include <algorithm>
#include <iostream>
#include <forward_list>
#include <fstream>
#include <ostream>

#include <boost/filesystem.hpp>

using namespace std;

namespace manifest
{
	using namespace boost::filesystem;

	const array<path, 4> projDirs = { path("CVS"),
	                                  path(".git"),
	                                  path(".svn"),
	                                  path(".hg") };

	bool is_project_directory (const path & p)
	{
		bool isproj = false;
		for (int i = 0; i < projDirs.size(); ++i) {
			isproj = exists(p / projDirs[i]);
			if (isproj) break;
		}

		return isproj;
	}

	int print_manifest (const path & p, ostream & out)
	{
		if (!exists(p)) {
			return 0;
		} else {
			// For project directories, output and escape immediately
			if ( is_project_directory(p) ) {
				out << ( p.native() ) << endl;
				return 1;
			}
			forward_list<path> children;
			directory_iterator end_it;
			for (directory_iterator it(p); it != end_it; ++it) {
				if ( is_directory(it->status()) ) {
					// Add to list of children to recurse down later
					children.push_front(it->path());
				}
			}
			// We've listed all the directories. Time to start searching them.
			int c = 0;
			for (auto it = children.begin(); it != children.end(); ++it) {
				c += print_manifest(*it, out);
			}
			// And that's it, we've recursed and counted all the projects
			return c;
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		cout << "usage: " << argv[0] << " /path/to/directory" << endl;
		return 1;
	}
	boost::filesystem::path projDir(argv[1]);
	manifest::print_manifest(projDir, cout);
}
