#include "util.h2"

bool     Util::s_keepAlive = false;
unsigned Util::s_repeatInterval = INT_MAX;
Selector Util::s_selector;