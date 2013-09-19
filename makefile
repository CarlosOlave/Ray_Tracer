# Makefile

CPP = g++
CFLAGS = -Wall -g -I. -I/usr/include/OpenEXR
LDFLAGS = -L/usr/local/lib -lIlmImf -lImath -lHalf
OBJS = main.o Vector2D.o Vector3D.o Mesh.o parse.o SceneReader.o Objects.o RayTracer.o Ray.o bvh_box.o BVH.o
INCLUDE = Vector2D.h Vector3D.h Mesh.h parse.h SceneReader.h Objects.h Vectors.h RayTracer.h Ray.h bvh_box.h BVH.h Surface.h

# Compile the program.
main_t06m01 : $(OBJS)
	$(CPP) $(CFLAGS) -o main_t06m01 $(OBJS) $(LDFLAGS)
	
main.o: main.cpp $(INCLUDE)
	$(CPP) $(CFLAGS) -c main.cpp

Vector2D.o: Vector2D.cpp $(INCLUDE)
	$(CPP) $(CFLAGS) -c Vector2D.cpp
	
Vector3D.o: Vector3D.cpp $(INCLUDE)
	$(CPP) $(CFLAGS) -c Vector3D.cpp

Mesh.o: Mesh.cpp $(INCLUDE)
	$(CPP) $(CFLAGS) -c Mesh.cpp

parse.o: parse.cpp $(INCLUDE)
	$(CPP) $(CFLAGS) -c parse.cpp

SceneReader.o: SceneReader.cpp $(INCLUDE)
	$(CPP) $(CFLAGS) -c SceneReader.cpp
	
Objects.o: Objects.cpp $(INCLUDE)
	$(CPP) $(CFLAGS) -c Objects.cpp

RayTracer.o: RayTracer.cpp $(INCLUDE)
	$(CPP) $(CFLAGS) -c RayTracer.cpp

Ray.o: Ray.cpp $(INCLUDE)
	$(CPP) $(CFLAGS) -c Ray.cpp

bvh_box.o: bvh_box.cpp $(INCLUDE)
	$(CPP) $(CFLAGS) -c bvh_box.cpp
	
BVH.o: BVH.cpp $(INCLUDE)
	$(CPP) $(CFLAGS) -c BVH.cpp

# command to be executed.
clean:
	rm -f main_t06m01 $(OBJS)
