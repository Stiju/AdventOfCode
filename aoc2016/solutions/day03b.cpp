#include "../common.h"

namespace day3b {
	struct Triangle {
		int x, y, z;
	};
	struct Triangles {
		Triangle t1, t2, t3;
	};
	std::istream& operator >> (std::istream& is, Triangles& triangles) {
		return is
			>> triangles.t1.x >> triangles.t2.x >> triangles.t3.x
			>> triangles.t1.y >> triangles.t2.y >> triangles.t3.y
			>> triangles.t1.z >> triangles.t2.z >> triangles.t3.z;
	}
	bool is_valid(const Triangle& triangle) {
		return (triangle.x + triangle.y) > triangle.z &&
			(triangle.y + triangle.z) > triangle.x &&
			(triangle.z + triangle.x) > triangle.y;
	}

	int get_valid_triangles(const std::string& input) {
		std::istringstream stream(input);
		Triangles triangles;
		int valid_triangles = 0;
		while(stream >> triangles) {
			if(is_valid(triangles.t1)) {
				++valid_triangles;
			}
			if(is_valid(triangles.t2)) {
				++valid_triangles;
			}
			if(is_valid(triangles.t3)) {
				++valid_triangles;
			}
		}
		return valid_triangles;
	}

	void run() {
		std::string input = read_file("input/day3.txt");
		std::cout << "day3b ";
		std::cout << get_valid_triangles(input) << '\n';
	}
}