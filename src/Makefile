# Makefile
# sagar, 2013-10-27 18:35


LIBS = -lglut -lGL -lGLU -lSDL -lSDL_image
objects = main.o textures.o game.o
INC=-I/usr/local/include/ -I/Users/lidan/Desktop/LineClipping/LineClipping/includes/


mario : $(objects)
	g++ -Wall $(LIB) $(INC) -framework OpenGL -framework IOKit -framework Cocoa -framework CoreVideo -o mario $(objects) $(LIBS)

main.o : main.cpp textures.h
	g++ -framework OpenGL -framework IOKit -framework Cocoa -framework CoreVideo -c main.cpp

textures.o : textures.cpp textures.cpp
	g++ -framework OpenGL -framework IOKit -framework Cocoa -framework CoreVideo  -c textures.cpp

game.o : game.cpp game.h
	g++ -framework OpenGL -framework IOKit -framework Cocoa -framework CoreVideo -c game.cpp

clean :
	rm $(objects) mario

# vim:ft=make
