// Copyright Amstad Digital 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "SculptedObject.generated.h"

static float SCULPT_PI = 3.14159265358979323846f;
static float SCULPT_TWOPI = SCULPT_PI * 2.0f;

UCLASS()
class SCULPTDROID_API ASculptedObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASculptedObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly)
		UProceduralMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		float SphereRadius = 100.0f;

	UPROPERTY(EditAnywhere)
		int32 SegmentLat = 22;

	UPROPERTY(EditAnywhere)
		int32 SegmentLon = 11;

	UPROPERTY(EditAnywhere)
		bool ReGen = false;



	UFUNCTION()
		void RecalculateNormalsAndTangents(bool bUpdateMesh = false);

	UFUNCTION(BlueprintCallable)
		int32 VerticiesInRange(FVector CenterPoint, float BrushRadius);

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// When created in the editor
	virtual void PostActorCreated() override;

	// When the scene is loaded (already in the map)
	virtual void PostLoad() override;

	//Update the mesh when the regen box is checked
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent);


	UFUNCTION()
		bool IsInBrushRange(FVector PointLocation, FVector CenterPoint, float BrushRange);



private:

	



#pragma region MeshGeneration
	// Generate the initial mesh
	UFUNCTION()
	void CreateMesh();
	UFUNCTION()
	void AddTriangle(int32 V1, int32 V2, int32 V3);
	UFUNCTION()
	void AddQuad(int32 A, int32 B, int32 C, int32 D);


	// Mesh data
	UPROPERTY()
	TArray<FVector> Vertices;
	UPROPERTY()
	TArray<int32> Triangles;
	UPROPERTY()
	TArray<FVector2D> UVs;
	UPROPERTY()
	TArray<FVector> NormalsArray;
	UPROPERTY()
	TArray<FProcMeshTangent> Tangents;
	UPROPERTY()
	TArray<FLinearColor> VertexColors;
#pragma endregion MeshGeneration

};
