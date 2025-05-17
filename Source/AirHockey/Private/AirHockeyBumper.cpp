#include "AirHockeyBumper.h"

#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

#include "Math/UnitConversion.h"

UAirHockeyBumper::UAirHockeyBumper()
{
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
} 

UPrimitiveComponent* GetRootPrimitiveComponent(AActor* InActor)
{
	UPrimitiveComponent* PrimitiveComponent = nullptr;

	if (InActor != nullptr)
	{
		USceneComponent* OwnerRootComponent = InActor->GetRootComponent();

		if (OwnerRootComponent != nullptr)
		{
			PrimitiveComponent = Cast<UPrimitiveComponent>(OwnerRootComponent);
		}
	}

	return PrimitiveComponent;
}

void UAirHockeyBumper::InitializeComponent()
{
	Super::InitializeComponent();

	UPrimitiveComponent* PrimitiveComponent = GetRootPrimitiveComponent(GetOwner());

	if (PrimitiveComponent != nullptr)
	{
		PrimitiveComponent->OnComponentHit.AddDynamic(this, &UAirHockeyBumper::OnHitCallback);
	}
}

void UAirHockeyBumper::UninitializeComponent()
{
	UPrimitiveComponent* PrimitiveComponent = GetRootPrimitiveComponent(GetOwner());

	if (PrimitiveComponent != nullptr)
	{
		PrimitiveComponent->OnComponentHit.RemoveDynamic(this, &UAirHockeyBumper::OnHitCallback);
	}

	Super::UninitializeComponent();
}

void UAirHockeyBumper::OnHitCallback(UPrimitiveComponent* InHitComp, AActor* InOtherActor, UPrimitiveComponent* InOtherComp, FVector InNormalImpulse, const FHitResult& InHit)
{
	if (InOtherComp != nullptr)
	{
		const FVector Force = -InHit.ImpactNormal * FUnitConversion::Convert(ForceIntensity, EUnit::Newtons, EUnit::KilogramCentimetersPerSecondSquared);
		const FVector ForceAppPoint = InHit.ImpactPoint;

		InOtherComp->AddForceAtLocation(Force, ForceAppPoint);
	}
}