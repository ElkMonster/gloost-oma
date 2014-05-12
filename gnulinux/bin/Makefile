




default:
	cd .. && make


help:
	@echo "Targets:"
	@echo "         default:  Builds contribs, gloost libraries and examples"
	@echo "         contrib:  Builds lib (libtinyxml.a)"
	@echo "         libs:     Builds contrib libs and libgloost.a"


contrib:
	cd ../contrib/tinyxml && make

libs:
	cd ../contrib/tinyxml && make
	cd ../library_build_with_make && make


fast:
	cd .. && make -j4

clean:
	cd .. && make clean
	cd ../contrib/tinyxml && make clean

realclean:
	make clean
	@rm -f *.so
	@rm -f *.a
	@rm -f *_* intergalactic
	@rm -f CON

