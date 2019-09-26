// Copyright Amstad Digital 2019

#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"


UENUM(BlueprintType)
enum class EAction : uint8
{
	None = 0,
	Mask_Edit,
	Sculpt_Edit,
	Camera_Zoom,
	Camera_Rotate,
	Camera_Pan,
	Camera_Pan_Zoom_Alt
};

UENUM(BlueprintType)
enum class ESculptTool : uint8
{
	Brush = 0,
	Inflate,
	Twist,
	Smooth,
	Flatten,	
	Pinch,
	Crease,
	Drag,
	Paint,
	Move,
	Masking,
	LocalScale,
	Transform
};


UENUM(BlueprintType)
enum class ESculptShader : uint8
{
	PBR = 0,
	Flat,
	Normal,
	Wireframe,
	UV,
	MatCap,
	Selection,
	Background,
	Merge,
	FXAA,
	Contour
};


UENUM(BlueprintType)
enum class ECameraMovementMode : uint8
{
	Orbit = 0,
	Spherical,
	Plane
};

UENUM(BlueprintType)
enum class EMultiState : uint8
{
	None = 0,
	Sculpt,
	Camera,
	Picking
};
