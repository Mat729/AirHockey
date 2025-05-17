#include "AirHockeyPaddleMovementComponent.h"

#include "Math/UnitConversion.h"

UAirHockeyPaddleMovementComponent::UAirHockeyPaddleMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PrePhysics;
}

void UAirHockeyPaddleMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

void UAirHockeyPaddleMovementComponent::TickComponent(float InDeltaTime, enum ELevelTick InTickType, FActorComponentTickFunction* InThisTickFunction)
{
	Super::TickComponent(InDeltaTime, InTickType, InThisTickFunction);

	UpdateSimulation(InDeltaTime);
}

void UAirHockeyPaddleMovementComponent::UpdateSimulation(float InDeltaTime)
{
	if (UpdatedPrimitive == nullptr)
	{
		return;
	}

	FBodyInstance* BodyInstance = UpdatedPrimitive->GetBodyInstance();

	if (BodyInstance == nullptr)
	{
		return;
	}

	const float ConvertedMaxForce = FUnitConversion::Convert(MaxForce, EUnit::Newtons, EUnit::KilogramCentimetersPerSecondSquared);
	const FVector ForceToAdd = InputControl * ConvertedMaxForce;

	BodyInstance->AddForce(ForceToAdd);

	if (MaxVelocity > 0.f)
	{
		const FVector CurrentVelocity = BodyInstance->GetUnrealWorldVelocity();

		const float ConvertedMaxVelocity = FUnitConversion::Convert(MaxVelocity, EUnit::MetersPerSecond, EUnit::CentimetersPerSecond);
		const FVector ClampedVelocity = CurrentVelocity.GetClampedToMaxSize(ConvertedMaxVelocity);

		BodyInstance->SetLinearVelocity(ClampedVelocity, false);
	}
}