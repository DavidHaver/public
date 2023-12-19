deque.out : ../../bin/obj/deque_test.o
	rm deque.out
	g++ -I../../include/ -std=c++11 -pedantic-errors -Wall -Wextra -g -fPIC  -o ../../bin/exe/deque.out $^ 
	ln -s ../../bin/exe/deque.out ./ 
../../bin/obj/deque_test.o : deque_test.cpp deque.hpp 
	g++ -I../../include/ -std=c++11 -pedantic-errors -Wall -Wextra -g -fPIC  -o ../../bin/obj/deque_test.o -c $< 
../../bin/obj/deque.o : deque.cpp deque.hpp 
	g++ -I../../include/ -std=c++11 -pedantic-errors -Wall -Wextra -g -fPIC  -o ../../bin/obj/deque.o -c $< 
libdeque.so : ../../bin/obj/deque.o deque.hpp 
	rm libdeque.so
	g++ -I../../include/ -std=c++11 -pedantic-errors -Wall -Wextra -g -fPIC  -o ../../bin/dll/libdeque.so -shared ../../bin/obj/deque.o 
	ln -s ../../bin/dll/libdeque.so ./ 
.PHONY : clean 
clean : 
	rm *.out *.so ../../bin/dll/libdeque.so ../../bin/exe/deque.out ../../bin/obj/deque_test.o ../../bin/obj/deque.o
