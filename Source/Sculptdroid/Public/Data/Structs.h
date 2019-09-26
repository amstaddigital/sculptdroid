// Copyright Amstad Digital 2019

#pragma once

#include "CoreMinimal.h"
#include "Structs.generated.h"


USTRUCT(BlueprintType)
struct FAABB
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Category = "AABB")
		FVector Min;

	UPROPERTY(BlueprintReadWrite, Category = "AABB")
		FVector Max;

	UPROPERTY(BlueprintReadWrite, Category = "AABB")
		FVector Center;

	FAABB()
	{
		Min = FVector(INFINITY, INFINITY, INFINITY);
		Max = FVector(-INFINITY, -INFINITY, -INFINITY);
		Center = FVector::ZeroVector;
	}

	// Returns a clone to store in a new AABB
	FAABB Clone()
	{
		FAABB NewAABB = FAABB();
		NewAABB.Min = Min;
		NewAABB.Max = Max;
		NewAABB.Center = Center;
		return NewAABB;
	}

	// Set this to argument
	void Copy(FAABB InAABB)
	{
		Min = InAABB.Min;
		Max = InAABB.Max;
	}

	// This had two versions one of a Vec3 and one with all floats to the arguments which is redundant in C++
	void Set(FVector NewMin, FVector NewMax)
	{
		Min = NewMin;
		Max = NewMax;
	}


};
