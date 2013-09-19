#include "SceneReader.h"
#include "RayTracer.h"
#include "Mesh.h"

int main(int ac, char **av) {
	
	if (ac < 2) {
		std::cout << "Missing Command" << std::endl;
	}
	
	SceneReader sceneReader;
	
	char* command = av[1];
	
	std::cout << "Parsing input file... " << std::endl;
	sceneReader.parse(command);
	std::cout << "Done!" << std::endl;
	
	RayTracer rt = RayTracer(sceneReader);
	std::cout << "Ray Tracing... " << std::endl;
	bool result = rt.DrawScene();
	if (!result) std::cout << "Error on rendering... " << std::endl;
	std::cout << "Done! image.exr" << std::endl;

	return 1;
}
