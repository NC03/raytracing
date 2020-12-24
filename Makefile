.DEFAULT_GOAL := all

CC = clang++
CFLAGS = -Wall -Werror
SRCDIR = source/
INCLUDE = -I$(SRCDIR)

all: color.o vector3d.o ray.o triangle.o sphere.o plane.o checkeredPlane.o checkeredSphere.o  scene.o raytracing.o raytracing

docs: source/*.h source/*.cpp
	doxygen Doxyfile
	make -Clatex/

raytracing: color.o vector3d.o ray.o triangle.o sphere.o plane.o checkeredPlane.o checkeredSphere.o  scene.o raytracing.o
	$(CC) $(CFLAGS) $(INCLUDE) *.o -pthread -o raytracing

triangle.o: $(SRCDIR)triangle.h $(SRCDIR)triangle.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)triangle.cpp

checkeredPlane.o: $(SRCDIR)checkeredPlane.h $(SRCDIR)checkeredPlane.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)checkeredPlane.cpp

checkeredSphere.o: $(SRCDIR)checkeredSphere.h $(SRCDIR)checkeredSphere.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)checkeredSphere.cpp

scene.o: $(SRCDIR)scene.h $(SRCDIR)scene.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)scene.cpp

sphere.o: $(SRCDIR)sphere.h $(SRCDIR)sphere.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)sphere.cpp

vector3d.o: $(SRCDIR)vector3d.h $(SRCDIR)vector3d.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)vector3d.cpp

color.o: $(SRCDIR)color.h $(SRCDIR)color.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)color.cpp

plane.o: $(SRCDIR)plane.cpp $(SRCDIR)plane.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)plane.cpp

ray.o: $(SRCDIR)ray.cpp $(SRCDIR)ray.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)ray.cpp

raytracing.o: $(SRCDIR)raytracing.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $(SRCDIR)raytracing.cpp

clean:
	rm *.o raytracing *.scene.stream