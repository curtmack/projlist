# change these as needed
CPP = g++ -std=c++11
LIBS = -Wl,-Bstatic -lboost_filesystem -lboost_system -Wl,-Bdynamic

# you might want to change these
PROJDIR = `pwd`
EXENAME = projlist
INSTALLDIR = ~/bin

exe : projlist.cpp
	${CPP} -o ${PROJDIR}/${EXENAME} projlist.cpp ${LIBS}

clean :
	rm -f ${PROJDIR}/${EXENAME} ${INSTALLDIR}/${EXENAME}

install : ${EXENAME}
	cp ${PROJDIR}/${EXENAME} ${INSTALLDIR}/
