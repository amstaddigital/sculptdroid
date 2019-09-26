// Copyright Amstad Digital 2019

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "Structs.generated.h"


USTRUCT(BlueprintType)
struct FProcMeshData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, Category = "Procedural Mesh Data")
		TArray<FVector> Vertices;

	UPROPERTY(BlueprintReadOnly, Category = "Procedural Mesh Data")
		TArray<int32> Triangles;

	UPROPERTY(BlueprintReadOnly, Category = "Procedural Mesh Data")
		TArray<FVector2D> UVs;

	UPROPERTY(BlueprintReadOnly, Category = "Procedural Mesh Data")
		TArray<FVector> NormalsArray;

	UPROPERTY(BlueprintReadOnly, Category = "Procedural Mesh Data")
		TArray<FProcMeshTangent> Tangents;

	UPROPERTY(BlueprintReadOnly, Category = "Procedural Mesh Data")
		TArray<FLinearColor> VertexColors;

	FProcMeshData() {}

	void AddTriangle(int32 A, int32 B, int32 C)
	{
		Triangles.Add(A);
		Triangles.Add(C);
		Triangles.Add(B);
	}

	void AddQuad(int32 A, int32 B, int32 C, int32 D)
	{
		Triangles.Add(A);
		Triangles.Add(C);
		Triangles.Add(B);

		Triangles.Add(A);
		Triangles.Add(D);
		Triangles.Add(C);
	}

};
