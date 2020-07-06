// Copyright @CloudStudio 2020

#include "BTService_PlayerDeadOrAlive.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

UBTService_PlayerDeadOrAlive::UBTService_PlayerDeadOrAlive() 
{
    NodeName = TEXT("Is Player Dead?");
}

void UBTService_PlayerDeadOrAlive::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AShooterCharacter* PlayerPawn = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    if (!ensure(PlayerPawn)) return;

    OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), PlayerPawn->IsCharacterDead());
}