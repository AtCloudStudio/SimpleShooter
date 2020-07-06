// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_PlayerDeadOrAlive.generated.h"

UCLASS()
class SIMPLESHOOTER_API UBTService_PlayerDeadOrAlive : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_PlayerDeadOrAlive();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};