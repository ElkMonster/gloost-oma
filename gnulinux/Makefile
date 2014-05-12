default:
	cd library_build_with_make && make
	cd ../tutorials/examples && make
	cd ../tutorials/essentials && make


clean:
	cd library_build_with_make && make clean
	cd ../tutorials/examples && make clean
	cd ../tutorials/essentials && make clean

realclean: clean
	cd library_build_with_make && make realclean
	cd ../tutorials/examples && make realclean
	cd ../tutorials/essentials && make realclean
	cd bin && make realclean

