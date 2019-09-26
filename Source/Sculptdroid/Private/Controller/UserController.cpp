// Copyright Amstad Digital 2019


#include "UserController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AUserController::AUserController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CamSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Cam Spring Arm"));
	RootComponent = CamSpringArm;
	CamSpringArm->bDoCollisionTest = false;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	MainCamera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AUserController::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = bShowMouseCursorOnStart;
}

// Called every frame
void AUserController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LimitCamera();

	if (bTouchSupport)
	{
		TouchRotation();
	}
}

// Called to bind functionality to input
void AUserController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Zoom", this, &AUserController::Zoom);
	PlayerInputComponent->BindAxis("MouseHorizontal", this, &AUserController::MouseHorizontal);
	PlayerInputComponent->BindAxis("MouseVertical", this, &AUserController::MouseVertical);

	PlayerInputComponent->BindAction("LeftClick", IE_Pressed, this, &AUserController::LeftMousePressed);
	PlayerInputComponent->BindAction("LeftClick", IE_Released, this, &AUserController::LeftMouseReleased);

	PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AUserController::OnTouchBegin);
	PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &AUserController::OnTouchEnd);
}

void AUserController::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	ResetCameraView();
}

void AUserController::ResetCameraView()
{
	if (CamSpringArm)
	{
		CamSpringArm->TargetArmLength = InitialCameraArmLength;
	}

	SetActorRotation(FRotator::ZeroRotator);
}

void AUserController::FocusToItem()
{
	UE_LOG(LogTemp, Warning, TEXT("Focusing on object"));
}




#pragma region Input
void AUserController::TouchRotation()
{
	if (!bGated)
	{
		float OutTouchX, OutTouchY;
		bool bCurrentlyTouching;
		UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetInputTouchState(ETouchIndex::Touch1, OutTouchX, OutTouchY, bCurrentlyTouching);
		FVector2D CurrentTouchPosition = FVector2D(OutTouchX, OutTouchY);

		CurrentTouchPosition -= TouchStartLocation;
		CurrentTouchPosition /= CamRotationSpeed;

		SetActorRotation(FRotator(GetActorRotation().Pitch, CurrentTouchPosition.X + RotationStart.Yaw, 0.0f));
		SetActorRelativeRotation(FRotator((CurrentTouchPosition.Y + RotationStart.Pitch) * -1, GetActorRotation().Yaw, 0.0f));
	}
}

void AUserController::Zoom(float AxisValue)
{
	if (AxisValue > 0.0f)
	{
		CamSpringArm->TargetArmLength -= 15;
	}
	else if(AxisValue < 0.0f)
	{
		CamSpringArm->TargetArmLength += 15;
	}
}

void AUserController::MouseHorizontal(float AxisValue)
{
	if (bHold)
	{
		AddActorWorldRotation(FRotator(0.0f, CamRotationSpeed*AxisValue, 0.0f));
	}
}

void AUserController::MouseVertical(float AxisValue)
{
	if (bHold)
	{
		AddActorLocalRotation(FRotator(CamRotationSpeed * AxisValue, 0.0f, 0.0f));
	}
}

void AUserController::LeftMousePressed()
{
	GetWorldTimerManager().SetTimer(InputHoldHandle, this, &AUserController::ActivateHold, 0.15f, true);
}

void AUserController::LeftMouseReleased()
{
	// TODO: Check for activated tool
	if (!bHold)
	{
		GetWorldTimerManager().ClearTimer(InputHoldHandle);
		FocusToItem();
	}
	bHold = false;
}

void AUserController::LimitCamera()
{
	if (bCamRotationYLimit)
	{
		if (GetActorRotation().Pitch < CamYLimit.GetLowerBoundValue() || GetActorRotation().Pitch > CamYLimit.GetUpperBoundValue())
		{
			FRotator FixedRotation = FRotator(CamYLimit.GetUpperBoundValue(), GetActorRotation().Yaw, 0.0f);
			
			if (GetActorRotation().Pitch < CamYLimit.GetLowerBoundValue())
			{
				FixedRotation = FRotator(CamYLimit.GetLowerBoundValue(), GetActorRotation().Yaw, 0.0f);
			}

			SetActorRotation(FixedRotation);
		}
	}
}

void AUserController::ActivateHold()
{
	bHold = true;
}

void AUserController::OnTouchBegin(ETouchIndex::Type TouchType, FVector TouchLocation)
{
	// TODO: Check for UI interaction
	TouchStartLocation = FVector2D(TouchLocation.X, TouchLocation.Y);
	RotationStart = GetActorRotation();
	GetWorldTimerManager().SetTimer(TouchHoldHandle, this, &AUserController::TouchHold, 0.15f, true);
}

void AUserController::OnTouchEnd(ETouchIndex::Type TouchType, FVector TouchLocation)
{
	bGated = true;
	bTouchHold = false;
}

void AUserController::TouchHold()
{
	bGated = false;
	float OutTouchX, OutTouchY;
	bool bCurrentlyTouching;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetInputTouchState(ETouchIndex::Touch1, OutTouchX, OutTouchY, bCurrentlyTouching);

	if (!bCurrentlyTouching)
	{
		TouchRotation();
	}
	else
	{
		GetWorldTimerManager().ClearTimer(TouchHoldHandle);
		FocusToItem();
	}
}

#pragma endregion Input