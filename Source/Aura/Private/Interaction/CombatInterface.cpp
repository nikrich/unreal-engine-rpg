// Copyright Hungry Ghost


#include "Interaction/CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.

FVector ICombatInterface::GetForwardVector() const
{
    return FVector();
}

FVector ICombatInterface::GetCombatSocketLocation() const
{
    return FVector();
}
