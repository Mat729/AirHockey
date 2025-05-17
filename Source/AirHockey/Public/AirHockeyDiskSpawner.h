#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AirHockeyDiskSpawner.generated.h"

class AAirHockeyDisk;

UCLASS()
class AIRHOCKEY_API AAirHockeyDiskSpawner : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Disk, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AAirHockeyDisk> DiskClass;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Disk, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<AActor> DiskSpawnPoint;

public:

	AAirHockeyDiskSpawner();

	virtual void BeginPlay() override;

protected:

	UFUNCTION(BlueprintCallable)
	void SpawnDisk();
};
