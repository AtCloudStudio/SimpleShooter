// Copyright @CloudStudio 2020

#include "BTTask_Shoot.h"
#include "AIModule/Classes/AIController.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot() 
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;

    AShooterCharacter* AIShooter = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if (!AIShooter) return EBTNodeResult::Failed;

    AIShooter->Shoot();

    return EBTNodeResult::Succeeded;
}