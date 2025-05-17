#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "AirHockeyPaddleMovementComponent.generated.h"

UCLASS()
class AIRHOCKEYPHYSICS_API UAirHockeyPaddleMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
	
private:

	UPROPERTY(Category = "Movement", EditAnywhere, meta = (Units = "N", UIMin = 0, ClampMin = 0))
	float MaxForce = 0.f;
	UPROPERTY(Category = "Movement", EditAnywhere, meta = (Units = "m/s", UIMin = 0, ClampMin = 0))
	float MaxVelocity = 0.f;

	UPROPERTY(Category = "Input", Transient, VisibleInstanceOnly)
	FVector InputControl = FVector::ZeroVector;

public:

	UAirHockeyPaddleMovementComponent();

	virtual void InitializeComponent() override;
	virtual void TickComponent(float InDeltaTime, enum ELevelTick InTickType, FActorComponentTickFunction* InThisTickFunction) override;

	void SetInputHorizontal(float InValue);
	void SetInputVertical(float InValue);

private:

	void UpdateSimulation(float InDeltaTime);
};

FORCEINLINE void UAirHockeyPaddleMovementComponent::SetInputHorizontal(float InValue)
{
	InputControl.X = InValue;
}

FORCEINLINE void UAirHockeyPaddleMovementComponent::SetInputVertical(float InValue)
{
	InputControl.Y = InValue;
}
