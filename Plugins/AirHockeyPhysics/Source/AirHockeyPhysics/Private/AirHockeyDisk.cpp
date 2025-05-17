#include "AirHockeyDisk.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

AAirHockeyDisk::AAirHockeyDisk()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));

	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetMassOverrideInKg(NAME_None, 1.0f, true);

	static FName CapsuleCollisionProfileName(TEXT("Disk"));
	CapsuleComponent->SetCollisionProfileName(CapsuleCollisionProfileName);

	CapsuleComponent->SetNotifyRigidBodyCollision(true);
	CapsuleComponent->SetGenerateOverlapEvents(true);
	CapsuleComponent->SetCapsuleSize(50.f, 100.f, false);
	
	CapsuleComponent->BodyInstance.bLockZTranslation = true;
	CapsuleComponent->BodyInstance.bLockXRotation = true;
	CapsuleComponent->BodyInstance.bLockYRotation = true;
	CapsuleComponent->BodyInstance.bLockZRotation = true;

	RootComponent = CapsuleComponent;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->PrimaryComponentTick.TickGroup = TG_PrePhysics;

	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinder<UStaticMesh> CyclinderMesh;
		FConstructorStatics()
			: CyclinderMesh(TEXT("/Engine/BasicShapes/Cylinder")) {}
	};

	static FConstructorStatics ConstructorStatics;
	MeshComponent->SetStaticMesh(ConstructorStatics.CyclinderMesh.Object);

	MeshComponent->SetRelativeScale3D(FVector(1.0f, 1.0f, 0.1f));
	static FName MeshCollisionProfileName(TEXT("NoCollision"));

	MeshComponent->SetCollisionProfileName(MeshCollisionProfileName);
	MeshComponent->SetNotifyRigidBodyCollision(false);
	MeshComponent->SetGenerateOverlapEvents(false);

	MeshComponent->SetupAttachment(CapsuleComponent);
}