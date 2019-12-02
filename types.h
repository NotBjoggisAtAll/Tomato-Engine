#ifndef TYPES_H
#define TYPES_H

#include <bitset>

using Entity = int;

const Entity MAX_ENTITIES = 5000;

using ComponentType = unsigned int;

const ComponentType MAX_COMPONENTS = 32;

/**
 * A Signature is a collection for bits that show which component belongs to which Entity.
 * Each Component has its own id which is the index of this bitset. If the bit is true the Entity has a copy of that component.
 */
using Signature = std::bitset<MAX_COMPONENTS>;


#endif // TYPES_H
