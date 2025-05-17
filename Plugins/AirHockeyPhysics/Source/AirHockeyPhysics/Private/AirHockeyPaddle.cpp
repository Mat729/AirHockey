#include "AirHockeyPaddle.h"

#include "AirHockeyPaddleMovementComponent.h"
#include "AirHockeyPaddleMagnetComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

#if WITH_EDITORONLY_DATA
#include "Components/ArrowComponent.h"
#endif // WITH_EDITORONLY_DATA

#include "Components/InputComponent.h"

#include "GameFramework/SpringArmComponent.h"

#include "Camera/CameraComponent.h"

AAirHockeyPaddle::AAirHockeyPaddle()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = ETickingGroup::TG_PrePhysics;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));

	CapsuleComponent->SetSimulatePhysics(true);
	CapsuleComponent->SetMassOverrideInKg(NAME_None, 2.0f, true);

	static FName CapsuleCollisionProfileName(TEXT("Pawn"));
	CapsuleComponent->SetCollisionProfileName(CapsuleCollisionProfileName);
	
	CapsuleComponent->SetNotifyRigidBodyCollision(true);
	CapsuleComponent->SetGenerateOverlapEvents(true);
	CapsuleComponent->SetCapsuleSize(75.f, 150.f, false);

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
	
	MeshComponent->SetRelativeScale3D(FVector(1.5f, 1.5f, 0.25f));
	static FName MeshCollisionProfileName(TEXT("NoCollision"));
	
	MeshComponent->SetCollisionProfileName(MeshCollisionProfileName);
	MeshComponent->SetNotifyRigidBodyCollision(false);
	MeshComponent->SetGenerateOverlapEvents(false);

	MeshComponent->SetupAttachment(CapsuleComponent);

#if WITH_EDITORONLY_DATA

	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));

	if (ArrowComponent != nullptr)
	{
		ArrowComponent->ArrowColor = FColor(0, 255, 0);
		ArrowComponent->ArrowSize = 2.f;
		ArrowComponent->ArrowLength = 350.f;

		ArrowComponent->SetupAttachment(CapsuleComponent);
	}

#endif // WITH_EDITORONLY_DATA

	SpringArmComponent = CreateOptionalDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	if (SpringArmComponent != nullptr)
	{
		SpringArmComponent->TargetArmLength = 750.f;
		SpringArmComponent->SocketOffset = FVector(0.f, 0.f, 300.f);
		SpringArmComponent->bDoCollisionTest = false;
		SpringArmComponent->bEnableCameraRotationLag = false;
		SpringArmComponent->bInheritPitch = false;
		SpringArmComponent->bInheritYaw = false;
		SpringArmComponent->bInheritRoll = false;

		SpringArmComponent->SetupAttachment(CapsuleComponent);
	}

	CameraComponent = CreateOptionalDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	if (CameraComponent != nullptr)
	{
		CameraComponent->SetupAttachment(SpringArmComponent);
	}

	MovementComponent = CreateDefaultSubobject<UAirHockeyPaddleMovementComponent>(TEXT("Movement"));

	MagnetComponent = CreateOptionalDefaultSubobject<UAirHockeyPaddleMagnetComponent>(TEXT("Magnet"));
}

void AAirHockeyPaddle::BeginPlay()
{
	Super::BeginPlay();
}

void AAirHockeyPaddle::SetupPlayerInputComponent(UInputComponent* InPlayerInputComponent)
{
	Super::SetupPlayerInputComponent(InPlayerInputComponent);

	if (InPlayerInputComponent == nullptr)
	{
		return;
	}

	InPlayerInputComponent->BindAxis("Horizontal", this, &AAirHockeyPaddle::SetInputHorizontal);
	InPlayerInputComponent->BindAxis("Vertical", this, &AAirHockeyPaddle::SetInputVertical);

	InPlayerInputComponent->BindAction("Magnet", IE_Pressed, this, &AAirHockeyPaddle::TurnOnMagnet);
	InPlayerInputComponent->BindAction("Magnet", IE_Released, this, &AAirHockeyPaddle::TurnOffMagnet);
}

void AAirHockeyPaddle::SetInputHorizontal(float InValue)
{
	if (MovementComponent != nullptr)
	{
		MovementComponent->SetInputHorizontal(InValue);
	}
}

void AAirHockeyPaddle::SetInputVertical(float InValue)
{
	if (MovementComponent != nullptr)
	{
		MovementComponent->SetInputVertical(InValue);
	}
}

void AAirHockeyPaddle::TurnOnMagnet()
{
	if (MagnetComponent != nullptr)
	{
		MagnetComponent->SetMagnetActive(true);
	}
}

void AAirHockeyPaddle::TurnOffMagnet()
{
	if (MagnetComponent != nullptr)
	{
		MagnetComponent->SetMagnetActive(false);
	}
}