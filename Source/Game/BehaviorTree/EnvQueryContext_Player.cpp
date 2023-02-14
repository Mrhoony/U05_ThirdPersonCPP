#include "EnvQueryContext_Player.h"
#include "Global.h"

#include "Characters/CEnemy_AI.h"
#include "Characters/CPlayer.h"
#include "Components/CBehaviorComponent.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UEnvQueryContext_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	ACEnemy_AI* aiPawn = Cast<ACEnemy_AI>(QueryInstance.Owner.Get());
	UCBehaviorComponent* behavior = CHelpers::GetComponent<UCBehaviorComponent>(aiPawn->GetController());

	if (behavior->GetTargetPlayer() != nullptr)
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, behavior->GetTargetPlayer());
}
