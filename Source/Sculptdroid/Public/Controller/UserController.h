// Copyright Amstad Digital 2019

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputCoreTypes.h"
#include "UserController.generated.h"

UCLASS()
class SCULPTDROID_API AUserController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUserController();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnConstruction(const FTransform& Transform) override;


	UPROPERTY(EditDefaultsOnly, Category = "User Controller | Input")
		bool bShowMouseCursorOnStart = true;

	UPROPERTY(EditDefaultsOnly, Category = "User Controller | Input")
		bool bTouchSupport = true;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "User Controller | Camera")
		bool bCamRotationYLimit = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "User Controller | Camera")
		FFloatRange CamYLimit = FFloatRange(-180.0f, 180.0f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "User Controller | Camera")
		float CamRotationSpeed = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "User Controller | Camera")
		float InitialCameraArmLength = 600.0f;




protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "User Controller")
		class USpringArmComponent* CamSpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "User Controller")
		class UCameraComponent* MainCamera;

	UPROPERTY(BlueprintReadWrite, Category = "User Controller | Touch Gate")
		bool bGated = true;

	
	UFUNCTION(BlueprintCallable, Category = "User Controller | Camera")
		void ResetCameraView();

	UFUNCTION(BlueprintCallable, Category = "User Controller | Camera")
		void FocusToItem();

	UFUNCTION(BlueprintCallable, Category = "User Controller | Touch")
		void TouchRotation();

private:
	UPROPERTY()
		bool bHold = false;

	UPROPERTY()
		bool bTouchHold = false;

	UPROPERTY()
		FVector2D TouchStartLocation = FVector2D::ZeroVector;

	UPROPERTY()
		FRotator RotationStart = FRotator::ZeroRotator;

	UPROPERTY()
		class AActor* FocusedActor = nullptr;

	UPROPERTY()
		class AActor* PrevFocusedActor = nullptr;

	UPROPERTY()
		FTimerHandle InputHoldHandle;

	UPROPERTY()
		FTimerHandle TouchHoldHandle;


	UFUNCTION()
		void Zoom(float AxisValue);

	UFUNCTION()
		void MouseHorizontal(float AxisValue);

	UFUNCTION()
		void MouseVertical(float AxisValue);

	UFUNCTION()
		void LeftMousePressed();

	UFUNCTION()
		void LeftMouseReleased();

	UFUNCTION()
		void LimitCamera();

	UFUNCTION()
		void ActivateHold();

	UFUNCTION()
		void OnTouchBegin(ETouchIndex::Type TouchType, FVector TouchLocation);

	UFUNCTION()
		void OnTouchEnd(ETouchIndex::Type TouchType, FVector TouchLocation);

	UFUNCTION()
		void TouchHold();


};
