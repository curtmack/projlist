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

	int genManifest (const path & p, ostream & out) {
		if (!exists(p)) {
			return 0;
		}
		else {
			forward_list<path> children;
			int c = 0;
			directory_iterator end_it;
			for (directory_iterator it(p);
			     it != end_it;
			     ++it) {
				if ( is_directory(it->status()) ) {
					if (it->path().filename() == ".git") {
						// This is a project directory, output and return immediately
						// Thank God for implicit resource management...
						out << ( p.native() ) << endl;
						return 1;
					}
					else {
						// Add to list of children to recurse down later
						children.push_front(it->path());
					}
				}
			}
			// We've listed all the directories. Time to start searching them.
			for (forward_list<path>::iterator it = children.begin();
			     it != children.end();
			     ++it) {
				c += genManifest(*it, out);
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
	manifest::genManifest(projDir, cout);
}
