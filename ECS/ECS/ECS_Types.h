#pragma once
#include <bitset>
#include <cstdint>
#include <exception>
#include "../../Worms/src/ExceptionHandling/ECS_Exception.h"

#define MAX_COMPONENTS 32
#define MAX_ENTITIES 1000
#define MAX_SYSTEMS 16

typedef uint16_t EntityId;
typedef uint8_t ComponentType;
typedef std::bitset<MAX_COMPONENTS> Signature;

#define ECS_VERBOSE 1

#if ECS_VERBOSE
#include "../../Worms/src/Terminal/Terminal.h"
class Terminal;
#define LOG(x) Terminal::Get().Log(x, LogLevel::INFO);
#else
#define LOG(x)
#endif

#ifndef ECS_THROW
#define ECS_THROW(message) throw std::exception(message)
#endif // !ECS_THROW

