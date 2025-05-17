#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AirHockeyPaddleMagnetComponent.generated.h"

class UPrimitiveComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIRHOCKEYPHYSICS_API UAirHockeyPaddleMagnetComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(Category = "Magnet", EditAnywhere, meta = (Units = "N", UIMin = 0, ClampMin = 0))
	float ForceIntensity = 0.f;
	UPROPERTY(Category = "Magnet", EditAnywhere, meta = (Units = "cm", UIMin = 0, ClampMin = 0))
	float MinRadius = 100.f;
	UPROPERTY(Category = "Magnet", EditAnywhere, meta = (Units = "cm", UIMin = 0, ClampMin = 0))
	float MaxRadius = 500.f;
	UPROPERTY(Category = "Magnet", EditAnywhere)
	TEnumAsByte<ECollisionChannel> TargetChannel;
	
	UPROPERTY(Category = "Magnet", EditAnywhere)
	bool bEnableDebugDrawer = false;

	UPROPERTY(Category = "Magnet", Transient, BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	bool bIsMagnetActive = false;
	UPROPERTY(Category = "Magnet", Transient, BlueprintReadOnly, VisibleInstanceOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UPrimitiveComponent*> OverlappingComponents;

public:

	UAirHockeyPaddleMagnetComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMagnetActive(bool InActive);

private:

	bool SphereOverlapComponents(TArray<UPrimitiveComponent*>& OutComponents);

	void DrawDebug();
};
