/**
 * @file uart.cpp
 * @brief Stub to load usci.cpp or suart.c
 */
#ifdef WITH_HUART
#include "usci.cpp"
#else
#include "suart.c"
#endif
