CPPFLAGS = g++ -I$(PATHI) -std=c++11 -pedantic-errors -Wall -Wextra -g -fPIC 
PATHI = ../../include/

% :
	mkdir src/$*
	echo "#include \"$*.hpp\"//header \n\nnamespace david_haver \n{ \n\n} //david_haver">src/$*/$*.cpp
	echo "#include \"my_assert.hpp\"//TEST SUMMARY \n#include \"$*.hpp\"//header \n\nusing namespace david_haver; \n\nint main() \n{ \n    SUMMARY; \n    return 0; \n}">src/$*/$*_test.cpp
	echo "#ifndef David_Haver_$*_hpp \n#define David_Haver_$*_hpp \n\nnamespace david_haver \n{ \n\n} //david_haver \n\n#endif //David_Haver_$*_hpp">src/$*/$*.hpp
	ln -s ../src/$*/$*_test.cpp test/
	ln -s ../src/$*/$*.hpp include/
	echo "$*.out : ../../bin/obj/$*_test.o ../../bin/obj/$*.o">src/$*/makefile
	echo "	$(CPPFLAGS) -o ../../bin/exe/$*.out $$^ ">>src/$*/makefile
	echo "	ln -f -s ../../bin/exe/$*.out ./ ">>src/$*/makefile
	echo "../../bin/obj/$*_test.o : $*_test.cpp $*.hpp ">>src/$*/makefile
	echo "	$(CPPFLAGS) -o ../../bin/obj/$*_test.o -c $$< ">>src/$*/makefile
	echo "../../bin/obj/$*.o : $*.cpp $*.hpp ">>src/$*/makefile
	echo "	$(CPPFLAGS) -o ../../bin/obj/$*.o -c $$< ">>src/$*/makefile
	echo "lib$*.so : ../../bin/obj/$*.o $*.hpp ">>src/$*/makefile
	echo "	$(CPPFLAGS) -o ../../bin/dll/lib$*.so -shared ../../bin/obj/$*.o ">>src/$*/makefile
	echo "	ln -f -s ../../bin/dll/lib$*.so ./ ">>src/$*/makefile
	echo ".PHONY : clean ">>src/$*/makefile
	echo "clean : ">>src/$*/makefile
	echo "	rm -f *.out *.so ../../bin/dll/lib$*.so ../../bin/exe/$*.out ../../bin/obj/$*_test.o ../../bin/obj/$*.o" >>src/$*/makefile
	
.PHONY: clean_%
clean_%:
	rm -f -r src/$*
	rm -f test/$*_test.cpp include/$*.hpp bin/dll/lib$*.so bin/exe/$*.out bin/obj/$*_test.o bin/obj/$*.o


