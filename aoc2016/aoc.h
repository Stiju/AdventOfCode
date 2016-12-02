#pragma once

#define DECLARE_RUN(x) namespace day##x { void run(); }
DECLARE_RUN(1a)
DECLARE_RUN(1b)

#undef DECLARE_RUN