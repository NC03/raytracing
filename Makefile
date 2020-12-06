.DEFAULT_GOAL := all
# -Iclasses/
CC = clang++
CFLAGS = -Wall -Werror

all: vector3d.o sphere.o color.o plane.o ray.o raytracing.o scene.o raytracing

scene.o: scene.h scene.cpp
	$(CC) $(CFLAGS) -c scene.cpp

sphere.o: sphere.h sphere.cpp
	$(CC) $(CFLAGS) -c sphere.cpp

vector3d.o: vector3d.h vector3d.cpp
	$(CC) $(CFLAGS) -c vector3d.cpp

color.o: color.h color.cpp
	$(CC) $(CFLAGS) -c color.cpp

plane.o: plane.cpp plane.h
	$(CC) $(CFLAGS) -c plane.cpp

ray.o: ray.cpp ray.h
	$(CC) $(CFLAGS) -c ray.cpp

raytracing.o: raytracing.cpp
	$(CC) $(CFLAGS) -c raytracing.cpp

raytracing: *.o
	$(CC) $(CFLAGS) *.o -o raytracing

clean:
	rm *.o raytracing