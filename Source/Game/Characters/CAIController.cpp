#include "CAIController.h"
#include "Global.h"

#include "CEnemy_AI.h"
#include "Components/CBehaviorComponent.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACAIController::ACAIController()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateActorComponent<UBlackboardComponent>(this, &Blackboard, "Blackboard");
	CHelpers::CreateActorComponent<UCBehaviorComponent>(this, &Behavior, "Behavior");
	CHelpers::CreateActorComponent<UAIPerceptionComponent>(this, &Perception, "Perception");

	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight");
	//TODO: Next
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerEnemy = Cast<ACEnemy_AI>(InPawn);
	UseBlackboard(OwnerEnemy->GetBehaviorTree()->BlackboardAsset, Blackboard);

	Behavior->SetBlackboard(Blackboard);
	
	RunBehaviorTree(OwnerEnemy->GetBehaviorTree());
}

void ACAIController::BeginPlay()			{	Super::BeginPlay();}
void ACAIController::Tick(float DeltaTime)	{	Super::Tick(DeltaTime);}
void ACAIController::OnUnPossess()			{	Super::OnUnPossess();}
