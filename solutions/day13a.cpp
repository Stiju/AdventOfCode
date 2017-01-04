#include "../common.h"

namespace day13a {
	union Point {
		struct {
			int x, y;
		} coords;
		uint64_t hash;
	};
	struct Position {
		Point pos;
		int distance;
	};

	int count_bits(int value) {
		int bits = 0, size = sizeof(value) * 8;
		for(int i = 0; i < size; ++i) {
			bits += (value >> i) & 1;
		}
		return bits;
	}

	bool is_wall(int x, int y, int favorite) {
		int v = x*x + 3 * x + 2 * x*y + y + y*y + favorite;
		return count_bits(v) & 1;
	}

	void add(const Position& check, std::unordered_set<uint64_t>& visited, std::queue<Position>& queue, int favorite) {
		if(check.pos.coords.x >= 0 && check.pos.coords.y >= 0 && !is_wall(check.pos.coords.x, check.pos.coords.y, favorite)) {
			if(visited.insert(check.pos.hash).second) {
				queue.push(check);
			}
		}
	};

	int shortest_path_distance(Point find, int favorite) {
		std::unordered_set<uint64_t> visited;
		std::queue<Position> queue;
		visited.insert(Point{{1,1}}.hash);
		queue.push({{{1, 1}}, 0});
		while(!queue.empty()) {
			auto current = queue.front();
			if(current.pos.hash == find.hash) {
				return current.distance;
			}
			queue.pop();
			int x = current.pos.coords.x, y = current.pos.coords.y, distance = current.distance + 1;
			add({{{x, y - 1}}, distance}, visited, queue, favorite);
			add({{{x + 1, y}}, distance}, visited, queue, favorite);
			add({{{x, y + 1}}, distance}, visited, queue, favorite);
			add({{{x - 1, y}}, distance}, visited, queue, favorite);
		}
		return 0;
	}

	int count_locations(int max_distance, int favorite) {
		std::unordered_set<uint64_t> visited;
		std::queue<Position> queue;
		visited.insert(Point{{1,1}}.hash);
		queue.push({{{1, 1}}, 0});
		while(!queue.empty()) {
			auto current = queue.front();
			if(current.distance == max_distance) {
				return visited.size();
			}
			queue.pop();
			int x = current.pos.coords.x, y = current.pos.coords.y, distance = current.distance + 1;
			add({{{x, y - 1}}, distance}, visited, queue, favorite);
			add({{{x + 1, y}}, distance}, visited, queue, favorite);
			add({{{x, y + 1}}, distance}, visited, queue, favorite);
			add({{{x - 1, y}}, distance}, visited, queue, favorite);
		}
		return 0;
	}

	void run() {
		std::cout << "day13a " << shortest_path_distance({{31, 39}}, 1350) << '\n';
		std::cout << "day13b " << count_locations(50, 1350) << '\n';
		//std::cout << shortest_path_distance({7, 4}, 10) << '\n';
	}
}
