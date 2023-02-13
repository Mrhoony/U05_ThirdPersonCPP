#include "CAIController.h"
#include "Global.h"

#include "CEnemy_AI.h"
#include "Components/CBehaviorComponent.h"
#include "CPlayer.h"

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
	Sight->SightRadius = 600.f;
	Sight->LoseSightRadius = 800.f;
	Sight->PeripheralVisionAngleDegrees = 90.f;
	Sight->SetMaxAge(2.f);

	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = false;
	Sight->DetectionByAffiliation.bDetectNeutrals = false;

	Perception->ConfigureSense(*Sight);
	Perception->SetDominantSense(Sight->GetSenseImplementation());
}

void ACAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	OwnerEnemy = Cast<ACEnemy_AI>(InPawn);
	UseBlackboard(OwnerEnemy->GetBehaviorTree()->BlackboardAsset, Blackboard);
	
	SetGenericTeamId(OwnerEnemy->GetTeamID());
	Perception->OnPerceptionUpdated.AddDynamic(this, &ACAIController::OnPerceptionUpdated);

	Behavior->SetBlackboard(Blackboard);
	
	RunBehaviorTree(OwnerEnemy->GetBehaviorTree());
}

void ACAIController::BeginPlay()			{	Super::BeginPlay();}
void ACAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(bDrawDebug);

	FVector center = OwnerEnemy->GetActorLocation();
	center.Z -= InitHeight;
	DrawDebugCircle(GetWorld(), center, Sight->SightRadius, 50, FColor::Green, false, -1, 0, 0, FVector::RightVector, FVector::ForwardVector); // SightRadius;
	DrawDebugCircle(GetWorld(), center, BehaviorRange, 50, FColor::Red, false, -1, 0, 0, FVector::RightVector, FVector::ForwardVector); // BehaviorRange;
}
void ACAIController::OnUnPossess()
{
	Super::OnUnPossess();
	Perception->OnPerceptionUpdated.Clear();
}

void ACAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
	TArray<AActor*> actors;
	Perception->GetCurrentlyPerceivedActors(nullptr, actors);

	ACPlayer* player = nullptr;
	for (AActor* actor : actors)
	{
		player = Cast<ACPlayer>(actor);
		if (player != nullptr) break;
	}

	Blackboard->SetValueAsObject("Player", player);
}

float ACAIController::GetSightRadius()
{
	return Sight->SightRadius;
}