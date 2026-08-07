// Copyright 2026 Silvan Teufel All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SquadFormationTypes.h"
#include "SquadComponent.generated.h"

/**
 * Put this on a leader/manager actor to move a group of AI agents in a coherent, navmesh-aware
 * formation. Add member pawns, pick a formation shape + spacing, and call MoveSquadTo — each member
 * is assigned a formation slot, the slot is projected onto the navmesh, and the member's AIController
 * is issued a move order to it.
 */
UCLASS(ClassGroup = (SquadFormation), meta = (BlueprintSpawnableComponent))
class SQUADFORMATION_API USquadComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	/** Formation the squad holds while moving. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SquadFormation")
	EFormationShape Shape = EFormationShape::Wedge;

	/** Distance between adjacent slots (cm). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SquadFormation", meta = (ClampMin = "1.0"))
	float Spacing = 150.f;

	/** Member agents that hold formation slots. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SquadFormation")
	TArray<TObjectPtr<AActor>> Members;

	UFUNCTION(BlueprintCallable, Category = "SquadFormation")
	void AddMember(AActor* Member);

	UFUNCTION(BlueprintCallable, Category = "SquadFormation")
	void RemoveMember(AActor* Member);

	/**
	 * Move the whole squad to Destination, holding formation. Each member's slot is projected onto
	 * the navmesh and issued as an AIController move order. Returns how many members were ordered.
	 */
	UFUNCTION(BlueprintCallable, Category = "SquadFormation")
	int32 MoveSquadTo(FVector Destination);

	/** World-space slot location for member Index around Destination, facing Facing (navmesh-projected). */
	UFUNCTION(BlueprintCallable, Category = "SquadFormation")
	FVector GetSlotWorldLocation(int32 Index, FVector Destination, FRotator Facing) const;

	/**
	 * Pure formation math: local-space slot offsets (X = forward, Y = right) for Count members.
	 * Static so it's unit-testable without an actor/world.
	 */
	static TArray<FVector> ComputeLocalOffsets(EFormationShape Shape, int32 Count, float Spacing);
};
