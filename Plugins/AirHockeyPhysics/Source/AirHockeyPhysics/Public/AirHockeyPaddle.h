#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AirHockeyPaddle.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

#if WITH_EDITORONLY_DATA
class UArrowComponent;
#endif // WITH_EDITORONLY_DATA

class USpringArmComponent;
class UCameraComponent;

class UInputComponent;

class UAirHockeyPaddleMovementComponent;
class UAirHockeyPaddleMagnetComponent;

UCLASS()
class AIRHOCKEYPHYSICS_API AAirHockeyPaddle : public APawn
{
	GENERATED_BODY()

public:

	AAirHockeyPaddle();

	virtual void SetupPlayerInputComponent(UInputComponent* InPlayerInputComponent) override;
	virtual void BeginPlay() override;

private:

	UPROPERTY(Category = Paddle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(Category = Paddle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;

#if WITH_EDITORONLY_DATA

	UPROPERTY()
	TObjectPtr<UArrowComponent> ArrowComponent;

#endif // WITH_EDITORONLY_DATA

	UPROPERTY(Category = Paddle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	UPROPERTY(Category = Paddle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(Category = Paddle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAirHockeyPaddleMovementComponent> MovementComponent;
	UPROPERTY(Category = Paddle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAirHockeyPaddleMagnetComponent> MagnetComponent;

	void SetInputHorizontal(float InValue);
	void SetInputVertical(float InValue);

	void TurnOnMagnet();
	void TurnOffMagnet();
};
