ACLOCAL_AMFLAGS = -I m4 --install

EXTRA_DIST = README UNLICENSE

bin_PROGRAMS = projlist

projlist_SOURCES = src/projlist.cpp
projlist_LDADD = -lboost_system -lboost_filesystem

README: README.md
	cp README.md README

