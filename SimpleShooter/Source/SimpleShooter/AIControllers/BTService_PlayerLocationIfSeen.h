// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooter/AIControllers/BTService_UpdatePlayerLocation.h"
#include "BTService_PlayerLocationIfSeen.generated.h"

UCLASS()
class SIMPLESHOOTER_API UBTService_PlayerLocationIfSeen : public UBTService_UpdatePlayerLocation
{
	GENERATED_BODY()

public:
	UBTService_PlayerLocationIfSeen();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};