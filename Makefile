run: lab1.cpp
	g++ lab1.cpp -lglut -lGLU -lGL -lGLEW -g
	./a.out
	
clean: 
	rm -f *.out *~ run
	
