deque.out : ../../bin/obj/deque_test.o
	g++ -I../../include/ -std=c++11 -pedantic-errors -Wall -Wextra -g -fPIC  -o ../../bin/exe/deque.out $^ 
	ln -f -s ../../bin/exe/deque.out ./ 
../../bin/obj/deque_test.o : deque_test.cpp deque.hpp 
	g++ -I../../include/ -std=c++11 -pedantic-errors -Wall -Wextra -g -fPIC  -o ../../bin/obj/deque_test.o -c $< 
../../bin/obj/deque.o : deque.cpp deque.hpp 
	g++ -I../../include/ -std=c++11 -pedantic-errors -Wall -Wextra -g -fPIC  -o ../../bin/obj/deque.o -c $< 
libdeque.so : ../../bin/obj/deque.o deque.hpp 
	g++ -I../../include/ -std=c++11 -pedantic-errors -Wall -Wextra -g -fPIC  -o ../../bin/dll/libdeque.so -shared ../../bin/obj/deque.o 
	ln -f -s ../../bin/dll/libdeque.so ./ 
.PHONY : clean 
clean : 
	rm  -f *.out *.so ../../bin/dll/libdeque.so ../../bin/exe/deque.out ../../bin/obj/deque_test.o ../../bin/obj/deque.o
