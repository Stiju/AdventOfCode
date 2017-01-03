#include "../common.h"

namespace day3a {
	struct Triangle {
		int x, y, z;
	};
	std::istream& operator >> (std::istream& is, Triangle& triangle) {
		return is >> triangle.x >> triangle.y >> triangle.z;
	}

	int get_valid_triangles(const std::string& input) {
		std::istringstream stream(input);
		Triangle triangle;
		int valid_triangles = 0;
		while(stream >> triangle) {
			if((triangle.x + triangle.y) > triangle.z && 
				(triangle.y + triangle.z) > triangle.x &&
				(triangle.z + triangle.x) > triangle.y) {
				++valid_triangles;
			}
		}
		return valid_triangles;
	}

	void run() {
		std::string input = read_file("input/day3.txt");
		std::cout << "day3a ";
		std::cout << get_valid_triangles(input) << '\n';
	}
}