#pragma once

#include "AbstractClasses/BaseActor.h"
#include "CoreMinimal.h"

#include "ShapeShifting.generated.h"

class UArrowComponent;

UENUM(BlueprintType)
enum EShapeType : uint8
{
	Box UMETA(DisplayName = "Box"),
	Capsule UMETA(DisplayName = "Capsule"),
	Sphere UMETA(DisplayName = "Sphere"),
};

UCLASS()
class UNREALPROGRAMGAME_API AShapeShifting : public ABaseActor
{
	GENERATED_BODY()

public:
	AShapeShifting();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape Shifting")
	float SweepDistance = 1000.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shape Shifting")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape Shifting")
	TObjectPtr<UArrowComponent> ArrowComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape Shifting")
	TEnumAsByte<EShapeType> ShapeType = Box;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape Shifting", meta = (EditCondition = "ShapeType == EShapeType::Box", EditConditionHides))
	FVector BoxExtend = FVector(40.0f, 40.0f, 40.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape Shifting", meta = (EditCondition = "ShapeType == EShapeType::Capsule", EditConditionHides))
	float CapsuleRadius = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape Shifting", meta = (EditCondition = "ShapeType == EShapeType::Capsule", EditConditionHides))
	float CapsuleHalfHeight = 25.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shape Shifting", meta = (EditCondition = "ShapeType == EShapeType::Sphere", EditConditionHides))
	float SphereRadius = 50.0f;
};