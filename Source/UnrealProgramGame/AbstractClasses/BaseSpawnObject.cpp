#include "BaseSpawnObject.h"

#include "UnrealProgramGameCustomCollision.h"

ABaseSpawnObject::ABaseSpawnObject()
{
	Mesh->SetSimulatePhysics(true);
	Mesh->SetCollisionResponseToChannel(ECC_Interact, ECR_Block);
}

void ABaseSpawnObject::Interact_Implementation(APawn* InteractingPawn)
{
	Message(FString::Printf(TEXT("Object picked up by %s"), *InteractingPawn->GetName()));

	Destroy();
}
