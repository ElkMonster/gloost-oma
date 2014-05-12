DUMMY := $(shell rm -f *~)
FILES =  $(wildcard ./*)
REALFILES = $(patsubst ./%, %, $(FILES))
SUBDIRSTMP = $(patsubst %Makefile, %, $(REALFILES))
SUBDIRSTMP1 = $(patsubst %Makefile_osx, %, $(SUBDIRSTMP))
SUBDIRSTMP2 = $(patsubst %examples.workspace, %, $(SUBDIRSTMP1))
SUBDIRSTMP3 = $(patsubst %examples_linux.workspace, %, $(SUBDIRSTMP2))
SUBDIRSTMP4 = $(patsubst %CVS, %, $(SUBDIRSTMP3))

SUBDIRS = $(patsubst %CVS, %, $(SUBDIRSTMP4))


default: 
	@for subdir in $(SUBDIRS) ; do \
	cd $$subdir && make $@ && cd ..;\
	done

clean:
	@for subdir in $(SUBDIRS) ; do \
	cd $$subdir && make $@ && cd ..;\
	done

realclean: clean
	@for subdir in $(SUBDIRS) ; do \
	cd $$subdir && make $@ && cd ..;\
	done






