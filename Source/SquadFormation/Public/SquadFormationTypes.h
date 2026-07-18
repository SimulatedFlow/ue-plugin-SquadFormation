// Copyright 2026 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SquadFormationTypes.generated.h"

/** The geometric shape a squad holds while moving. */
UENUM(BlueprintType)
enum class EFormationShape : uint8
{
	Column  UMETA(DisplayName = "Column"),  // single file behind the leader
	Line    UMETA(DisplayName = "Line"),    // shoulder-to-shoulder
	Wedge   UMETA(DisplayName = "Wedge"),   // V behind the leader
	Circle  UMETA(DisplayName = "Circle"),  // ring around the center
	Box     UMETA(DisplayName = "Box")      // filled grid
};
