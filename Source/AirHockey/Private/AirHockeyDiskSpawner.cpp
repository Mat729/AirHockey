#include "AirHockeyDiskSpawner.h"

#include "AirHockeyDisk.h"

AAirHockeyDiskSpawner::AAirHockeyDiskSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AAirHockeyDiskSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnDisk();
}

void AAirHockeyDiskSpawner::SpawnDisk()
{
	if (DiskClass == nullptr)
	{
		return;
	}

	if (DiskSpawnPoint == nullptr)
	{
		return;
	}

	GetWorld()->SpawnActor<AActor>(DiskClass, DiskSpawnPoint->GetTransform());
}