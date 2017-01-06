#include "aoc.h"
#include "stopwatch.h"

#define RUN(x) day##x::run()

int main() {
	std::ios::sync_with_stdio(false);
	StopWatch sw;
	RUN(1a);
	RUN(1b);
	RUN(2a);
	RUN(2b);
	RUN(3a);
	RUN(3b);
	RUN(4a);
	RUN(4b);
	RUN(5a);
	RUN(5b);
	RUN(6a);
	RUN(6b);
	RUN(7a);
	RUN(7b);
	RUN(8a);
	RUN(9a);
	RUN(9b);
	RUN(10a);
	//RUN(11a);
	RUN(12a);
	RUN(13a);
	RUN(14a);
}

#undef RUN