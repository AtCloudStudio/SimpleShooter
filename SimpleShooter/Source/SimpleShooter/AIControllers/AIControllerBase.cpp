// Copyright @CloudStudio 2020

#include "AIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
// #include "Kismet/GameplayStatics.h"
// #include "SimpleShooter/Characters/PlayerShooter.h"

AAIControllerBase::AAIControllerBase() 
{
    PrimaryActorTick.bCanEverTick = false;
}

void AAIControllerBase::BeginPlay() 
{
    Super::BeginPlay();

    if (!ensure(AIBehavior || GetPawn())) return;
    
    RunBehaviorTree(AIBehavior);
    GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
}

void AAIControllerBase::Tick(float DeltaSeconds) 
{
    Super::Tick(DeltaSeconds);
}

// void AAIControllerBase::FocusOnPlayer(APawn* Player)
// {
//     if (LineOfSightTo(Player))
//     {
//         SetFocus(Player);
//         MoveToActor(Player, 100.0f);
//     }
//     else 
//     {
//         ClearFocus(EAIFocusPriority::LastFocusPriority);
//         StopMovement();
//     }
// }

// void AAIControllerBase::SetAIEnabledState(bool bIsAIEnabled) 
// {
//     if (bIsAIEnabled)
// 	{
// 		GetPawn()->SetActorTickEnabled(true);
// 	}
// 	else
// 	{
// 		GetPawn()->SetActorTickEnabled(false);
// 	}
// }