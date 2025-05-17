#include "AirHockeyPaddleMagnetComponent.h"

#include "Math/UnitConversion.h"

#include "DrawDebugHelpers.h"

static TAutoConsoleVariable<int32> CVarEnableDebugDrawer(
	TEXT("AirHockeyPaddleMagnet.EnableDebugDrawer"),
	0,
	TEXT("Draw magnet debug info.\n"));

UAirHockeyPaddleMagnetComponent::UAirHockeyPaddleMagnetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = TG_PrePhysics;
}

void UAirHockeyPaddleMagnetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	bool bHasValidOverlap = SphereOverlapComponents(OverlappingComponents);

	if (bIsMagnetActive && bHasValidOverlap)
	{
		const int32 NumOverlappingComponents = OverlappingComponents.Num();

		for (int32 Index = 0; Index < NumOverlappingComponents; ++Index)
		{
			UPrimitiveComponent* PrimitiveComponent = OverlappingComponents[Index];

			if (PrimitiveComponent != nullptr)
			{
				FVector Distance = GetOwner()->GetActorLocation() - PrimitiveComponent->GetComponentTransform().GetLocation();
				Distance.Z = 0.f;

				const FVector ForceDir = Distance.GetSafeNormal();
				
				FVector ForceToApply = ForceDir * FUnitConversion::Convert(ForceIntensity, EUnit::Newtons, EUnit::KilogramCentimetersPerSecondSquared);

				const float ForceScale = FMath::GetMappedRangeValueClamped(FVector2D(MinRadius, MaxRadius), FVector2D(0.f, 1.f), Distance.Size());
				ForceToApply *= ForceScale;

				PrimitiveComponent->AddForce(ForceToApply);
			}
		}
	}

	if (bEnableDebugDrawer || CVarEnableDebugDrawer.GetValueOnAnyThread())
	{
		DrawDebug();
	}
}

void UAirHockeyPaddleMagnetComponent::SetMagnetActive(bool InActive)
{
	bIsMagnetActive = InActive;
}

bool UAirHockeyPaddleMagnetComponent::SphereOverlapComponents(TArray<UPrimitiveComponent*>& OutComponents)
{
	OutComponents.Empty();

	TArray<FOverlapResult> Overlaps;

	const FVector SphereLocation = GetOwner()->GetActorLocation();

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(TargetChannel);

	GetWorld()->OverlapMultiByObjectType(Overlaps, SphereLocation, FQuat::Identity, ObjectParams, FCollisionShape::MakeSphere(MaxRadius));

	const int32 NumOverlaps = Overlaps.Num();

	for (int32 OverlapIndex = 0; OverlapIndex < NumOverlaps; ++OverlapIndex)
	{
		const FOverlapResult& Overlap = Overlaps[OverlapIndex];
		if (Overlap.Component.IsValid())
		{
			OutComponents.Add(Overlap.Component.Get());
		}
	}

	return (OutComponents.Num() > 0);
}

void UAirHockeyPaddleMagnetComponent::DrawDebug()
{
#if UE_ENABLE_DEBUG_DRAWING

	const FVector OwnerLocation = GetOwner()->GetActorLocation();

	//DrawDebugSphere(GetWorld(), OwnerLocation, MaxRadius, 32, FColor::Red, false, -1.f, SDPG_Foreground);

	DrawDebugCylinder(GetWorld(), OwnerLocation - FVector::UpVector * 10.f, OwnerLocation + FVector::UpVector * 10.f, MaxRadius, 32, FColor::Red, false, -1.f, SDPG_World);

	const int32 NumOverlappingComponents = OverlappingComponents.Num();

	for (int32 Index = 0; Index < NumOverlappingComponents; ++Index)
	{
		UPrimitiveComponent* PrimitiveComponent = OverlappingComponents[Index];

		if (PrimitiveComponent != nullptr)
		{
			const FVector TargetLocation = PrimitiveComponent->GetComponentTransform().GetLocation();

			DrawDebugLine(GetWorld(), OwnerLocation, TargetLocation, FColor::Red, false, -1.f, SDPG_Foreground);
		}
	}

#endif // UE_ENABLE_DEBUG_DRAWING
}