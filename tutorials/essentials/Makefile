DUMMY := $(shell rm -f *~)
FILES =  $(wildcard ./*)
REALFILES = $(patsubst ./%, %, $(FILES))
SUBDIRSTMP = $(patsubst %Makefile, %, $(REALFILES))
SUBDIRSTMP1 = $(patsubst %Makefile_osx, %, $(SUBDIRSTMP))
SUBDIRSTMP2 = $(patsubst %essentials.workspace, %, $(SUBDIRSTMP1))
SUBDIRSTMP3 = $(patsubst %CVS, %, $(SUBDIRSTMP2))

SUBDIRS = $(patsubst %CVS, %, $(SUBDIRSTMP3))

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






