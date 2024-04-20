#pragma once;
#include <bitset>
#include <cstdint>

#define MAX_COMPONENTS 32
#define MAX_ENTITIES 1000
#define MAX_SYSTEMS 16

typedef uint16_t Entity;
typedef uint8_t ComponentType;
typedef std::bitset<MAX_COMPONENTS> Signature;