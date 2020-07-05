// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

UCLASS()
class SIMPLESHOOTER_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AAIControllerBase();
	virtual void Tick(float DeltaSeconds) override;
	// void SetAIEnabledState(bool bIsAIEnabled);

private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* AIBehavior;

protected:
	virtual void BeginPlay() override;
};