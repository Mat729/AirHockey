#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirHockeyDisk.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;

UCLASS()
class AIRHOCKEYPHYSICS_API AAirHockeyDisk : public AActor
{
	GENERATED_BODY()

public:

	AAirHockeyDisk();

private:

	UPROPERTY(Category = Paddle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(Category = Paddle, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> MeshComponent;
};