objects = .obj/main.o  \
          .obj/oper.o  \
          .obj/polishmachine.o  \
          .obj/stackmachine.o

headers = src/oper.h  \
          src/polishmachine.h  \
          src/stackmachine.h  \
          src/list.h

calculator : $(objects)
	g++ $^ -o $@

.obj/main.o : src/main.cpp $(headers)
	g++ -c src/main.cpp -o $@

.obj/oper.o : src/oper.cpp src/oper.h
	g++ -c src/oper.cpp -o $@

.obj/polishmachine.o : src/polishmachine.cpp  \
                       src/polishmachine.h src/oper.h src/list.h
	g++ -c src/polishmachine.cpp -o $@

.obj/stackmachine.o : src/stackmachine.cpp  \
                      src/stackmachine.h src/oper.h src/list.h
	g++ -c src/stackmachine.cpp -o $@

clean :
	rm .obj/*.o

