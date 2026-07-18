// Copyright 2026 Silvan Teufel / Teufel-Engineering.com All Rights Reserved.

#include "SquadComponent.h"
#include "SquadFormationLog.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "NavigationData.h"

void USquadComponent::AddMember(AActor* Member)
{
	if (Member)
	{
		Members.AddUnique(Member);
	}
}

void USquadComponent::RemoveMember(AActor* Member)
{
	Members.Remove(Member);
}

TArray<FVector> USquadComponent::ComputeLocalOffsets(EFormationShape Shape, int32 Count, float Spacing)
{
	TArray<FVector> Offsets;
	if (Count <= 0)
	{
		return Offsets;
	}
	Offsets.Reserve(Count);
	Spacing = FMath::Max(1.f, Spacing);

	switch (Shape)
	{
	case EFormationShape::Column:
		for (int32 i = 0; i < Count; ++i)
		{
			Offsets.Add(FVector(-i * Spacing, 0.f, 0.f)); // single file behind
		}
		break;

	case EFormationShape::Line:
		for (int32 i = 0; i < Count; ++i)
		{
			const float Y = (i - (Count - 1) * 0.5f) * Spacing;
			Offsets.Add(FVector(0.f, Y, 0.f));
		}
		break;

	case EFormationShape::Wedge:
		Offsets.Add(FVector::ZeroVector); // tip = leader
		for (int32 i = 1; i < Count; ++i)
		{
			const int32 Rank = (i + 1) / 2;
			const float Side = (i % 2 == 1) ? 1.f : -1.f;
			Offsets.Add(FVector(-Rank * Spacing, Side * Rank * Spacing, 0.f));
		}
		break;

	case EFormationShape::Circle:
	{
		const float Radius = FMath::Max(Spacing, (Spacing * Count) / (2.f * PI));
		for (int32 i = 0; i < Count; ++i)
		{
			const float Ang = (2.f * PI * i) / Count;
			Offsets.Add(FVector(FMath::Cos(Ang) * Radius, FMath::Sin(Ang) * Radius, 0.f));
		}
		break;
	}

	case EFormationShape::Box:
	default:
	{
		const int32 Cols = FMath::Max(1, FMath::CeilToInt(FMath::Sqrt((float)Count)));
		for (int32 i = 0; i < Count; ++i)
		{
			const int32 Row = i / Cols;
			const int32 Col = i % Cols;
			const float Y = (Col - (Cols - 1) * 0.5f) * Spacing;
			Offsets.Add(FVector(-Row * Spacing, Y, 0.f));
		}
		break;
	}
	}
	return Offsets;
}

FVector USquadComponent::GetSlotWorldLocation(int32 Index, FVector Destination, FRotator Facing) const
{
	const TArray<FVector> Offsets = ComputeLocalOffsets(Shape, Members.Num(), Spacing);
	if (!Offsets.IsValidIndex(Index))
	{
		return Destination;
	}
	const FVector World = Destination + Facing.RotateVector(Offsets[Index]);

	// Snap onto the navmesh so agents don't get slots off the walkable surface.
	if (UWorld* W = GetWorld())
	{
		if (UNavigationSystemV1* Nav = FNavigationSystem::GetCurrent<UNavigationSystemV1>(W))
		{
			FNavLocation Projected;
			if (Nav->ProjectPointToNavigation(World, Projected, FVector(Spacing, Spacing, Spacing * 2.f)))
			{
				return Projected.Location;
			}
		}
	}
	return World;
}

int32 USquadComponent::MoveSquadTo(FVector Destination)
{
	const int32 Count = Members.Num();
	if (Count == 0)
	{
		return 0;
	}

	// Face the direction of travel (from the squad's average position toward the destination).
	FVector Center = FVector::ZeroVector;
	int32 Valid = 0;
	for (const TObjectPtr<AActor>& M : Members)
	{
		if (M)
		{
			Center += M->GetActorLocation();
			++Valid;
		}
	}
	if (Valid > 0)
	{
		Center /= Valid;
	}
	const FVector Dir = (Destination - Center).GetSafeNormal2D();
	const FRotator Facing = Dir.IsNearlyZero() ? FRotator::ZeroRotator : Dir.Rotation();

	int32 Ordered = 0;
	for (int32 i = 0; i < Count; ++i)
	{
		AActor* Member = Members[i];
		if (!Member)
		{
			continue;
		}
		const FVector Slot = GetSlotWorldLocation(i, Destination, Facing);
		if (APawn* Pawn = Cast<APawn>(Member))
		{
			if (AAIController* AI = Cast<AAIController>(Pawn->GetController()))
			{
				AI->MoveToLocation(Slot, /*AcceptanceRadius*/ Spacing * 0.4f);
				++Ordered;
			}
		}
	}

	UE_LOG(LogSquadFormation, Verbose, TEXT("MoveSquadTo: ordered %d/%d members in %s formation."),
		Ordered, Count, *UEnum::GetValueAsString(Shape));
	return Ordered;
}
