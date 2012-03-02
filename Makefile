OPT = -g3

objects = .obj/main.o  \
          .obj/oper.o  \
          .obj/polishmachine.o  \
          .obj/stackmachine.o \
		  .obj/stretchablestack.o

headers = src/oper.h  \
          src/polishmachine.h  \
          src/stackmachine.h  \
		  src/list.h \
		  src/stretchablestack.h

calculator : $(objects)
	g++ ${OPT} $^ -o $@

.obj/main.o : src/main.cpp $(headers)
	g++ ${OPT} -c src/main.cpp -o $@

.obj/oper.o : src/oper.cpp src/oper.h
	g++ ${OPT} -c src/oper.cpp -o $@

.obj/polishmachine.o : src/polishmachine.cpp  \
                       src/polishmachine.h src/oper.h src/list.h
	g++ ${OPT} -c src/polishmachine.cpp -o $@

.obj/stackmachine.o : src/stackmachine.cpp  \
                      src/stackmachine.h src/oper.h src/stretchablestack.h
	g++ ${OPT} -c src/stackmachine.cpp -o $@

.obj/stretchablestack.o : src/stretchablestack.cpp src/stretchablestack.h
	g++ ${OPT} -c src/stretchablestack.cpp -o $@

clean :
	rm .obj/*.o

