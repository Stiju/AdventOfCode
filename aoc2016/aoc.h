#pragma once

#define DECLARE_RUN(x) namespace day##x { void run(); }
DECLARE_RUN(1a)
DECLARE_RUN(1b)
DECLARE_RUN(2a)
DECLARE_RUN(2b)
#undef DECLARE_RUN