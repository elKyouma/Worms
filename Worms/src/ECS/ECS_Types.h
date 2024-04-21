#pragma once;
#include <bitset>
#include <cstdint>
#include <exception>
#define MAX_COMPONENTS 32
#define MAX_ENTITIES 1000
#define MAX_SYSTEMS 16

typedef uint16_t Entity;
typedef uint8_t ComponentType;
typedef std::bitset<MAX_COMPONENTS> Signature;

#ifndef ECS_THROW
#define ECS_THROW(message) throw std::exception(message)
#endif // !ECS_THROW
