#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AirHockeyBumper.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRHOCKEY_API UAirHockeyBumper : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(Category = "Bumper", EditAnywhere, meta = (Units = "N", UIMin = 0, ClampMin = 0))
	float ForceIntensity = 0.f;

public:	

	UAirHockeyBumper();

	virtual void InitializeComponent() override;
	virtual void UninitializeComponent() override;

private:

	UFUNCTION()
	void OnHitCallback(UPrimitiveComponent* InHitComp, AActor* InOtherActor, UPrimitiveComponent* InOtherComp, FVector InNormalImpulse, const FHitResult& InHit);
};