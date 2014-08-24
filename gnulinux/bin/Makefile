




default:
	cd .. && make


help:
	@echo "Targets:"
	@echo "         default:  Builds contribs, gloost libraries and examples"
	@echo "         libs:     Builds contrib libs and libgloost.a"


libs:
	cd ../library_build_with_make && make


fast:
	cd .. && make -j4

clean:
	cd .. && make clean

realclean:
	make clean
	@rm -f *.so
	@rm -f *.a
	@rm -f CON

