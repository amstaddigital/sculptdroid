// Copyright Amstad Digital 2019

#include "SculptedObject.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
ASculptedObject::ASculptedObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
	RootComponent = Mesh;
	Mesh->bUseAsyncCooking = true;

}

// Called when the game starts or when spawned
void ASculptedObject::BeginPlay()
{
	Super::BeginPlay();
	
}


void ASculptedObject::PostActorCreated()
{
	Super::PostActorCreated();
	CreateMesh();
	
}

void ASculptedObject::PostLoad()
{
	Super::PostLoad();
	CreateMesh();
}


void ASculptedObject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (ReGen)
	{
		ReGen = false;
		CreateMesh();
	}

}

// Called every frame
void ASculptedObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASculptedObject::CreateMesh()
{
	Vertices.Empty();
	int32 Index = 0;

	/* Sphere generation code modified from https://github.com/caosdoar/spheres/blob/master/src/spheres.cpp */

	// Generate UV sphere
	for (int32 m = 0; m < SegmentLat - 1; m++)
	{
		const float Polar = SCULPT_PI * ((float)m + 1) / SegmentLat;
		const float SinPol = FMath::Sin(Polar);
		const float CosPol = FMath::Cos(Polar);

		for (int32 n = 0; n < SegmentLon; n++)
		{
			const float Azimuth = 2.0 * SCULPT_PI * ((float)n) / SegmentLon;
			const float SinAz = FMath::Sin(Azimuth);
			const float CosAz = FMath::Cos(Azimuth);

			float x = SinPol * CosAz;
			float y = CosPol;
			float z = SinPol * SinAz;

			FVector NewVertex = FVector(x, y, z) * Radius;
			Vertices.Add(NewVertex);

			//UE_LOG(LogTemp, Warning, TEXT("%d: Adding %s"), Index, *NewVertex.ToString());
			Index++;
		}
	}



	Triangles.Empty();
	// Sphere cap
	for (int32 i = 0; i < SegmentLon; i++)
	{
		int32 A = i + 1;
		int32 B = (i + 1) % SegmentLon + 1;

		AddTriangle(0, B, A);
		//UE_LOG(LogTemp, Warning, TEXT("Adding triangle (%d, %d, %d)"), 0, B, A);
	}

	// Sphere body
	for (int32 j = 0; j < SegmentLat - 2; j++)
	{
		int32 AStart = j * SegmentLon + 1;
		int32 BStart = (j + 1) * SegmentLon + 1;

		for (int32 i = 0; i < SegmentLon; i++)
		{
			int32 A = AStart + i;
			int32 A1 = AStart + (i + 1) % SegmentLon;
			int32 B = BStart + i;
			int32 B1 = BStart + (i + 1) % SegmentLon;
			AddQuad(A, A1, B1, B);
		}
	}

	// Sphere cap
	for (int32 i = 0; i < SegmentLon; i++)
	{
		int32 A = i + SegmentLon * (SegmentLat - 2) + 1;
		int32 B = (i + 1) % SegmentLon + SegmentLon * (SegmentLat - 2) + 1;

		AddTriangle(Vertices.Num() - 1, A, B);
	}

	VertexColors.Reset();

	RecalculateNormalsAndTangents();



	// Assemble the mesh from the components
	Mesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, NormalsArray, UVs, VertexColors, Tangents, true);

	// Enable collision data
	// Mesh->ContainsPhysicsTriMeshData(true);*/
	Mesh->ContainsPhysicsTriMeshData(true);



	/*
	UVs.Reset();
	UVs.AddUninitialized(Vertices.Num());

	for (int Lat = 0; Lat < SegLat; Lat++)
	{
		for (int Lon = 0; Lon < SegLon; Lon++)
		{
			UVs[Lon + Lat * (SegLon + 1) + 1] = FVector2D((float)Lon / SegLon, 1.0f - (float)(Lat + 1) / (SegLat + 1));
		}
	}
	// Should be the same as FVector::UpVector
	UVs[0] = FVector2D(0, 1);
	UVs[UVs.Num() - 1] = FVector2D::ZeroVector;
	*/

}


void ASculptedObject::RecalculateNormalsAndTangents(bool bUpdateMesh)
{
	NormalsArray.Empty();
	Tangents.Empty();
	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UVs, NormalsArray, Tangents);

	if (bUpdateMesh)
	{
		Mesh->UpdateMeshSection_LinearColor(0, Vertices, NormalsArray, UVs, VertexColors, Tangents);
	}
	
}


int32 ASculptedObject::VerticiesInRange(FVector CenterPoint, float BrushRadius)
{
	int32 Count = 0;
	for (FVector ElemVec : Vertices)
	{
		if (IsInBrushRange(ElemVec, CenterPoint, BrushRadius))
		{
			Count++;
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("VertArrayCount: %d"), Vertices.Num());
	return Count;
}

bool ASculptedObject::IsInBrushRange(FVector PointLocation, FVector CenterPoint, float BrushRange)
{
	CenterPoint = FVector(
		FMath::Abs(CenterPoint.X) + BrushRange, 
		FMath::Abs(CenterPoint.Y) + BrushRange,
		FMath::Abs(CenterPoint.Z) + BrushRange);

	bool bXInRange = FMath::Abs(PointLocation.X) <= CenterPoint.X;
	bool bYInRange = FMath::Abs(PointLocation.Y) <= CenterPoint.Y;
	bool bZInRange = FMath::Abs(PointLocation.Z) <= CenterPoint.Z;

	return bXInRange && bYInRange && bZInRange;
}










void ASculptedObject::AddTriangle(int32 V1, int32 V2, int32 V3)
{
	Triangles.Add(V1);
	Triangles.Add(V3);
	Triangles.Add(V2);
	
}

void ASculptedObject::AddQuad(int32 A, int32 B, int32 C, int32 D)
{
	Triangles.Add(A);
	Triangles.Add(C);
	Triangles.Add(B);
	

	Triangles.Add(A);
	Triangles.Add(D);
	Triangles.Add(C);
	
}

