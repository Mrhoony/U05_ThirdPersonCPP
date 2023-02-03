#include "CDoAction_Melee.h"
#include "Global.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "GameFramework/Character.h"

void ACDoAction_Melee::DoAction()
{
	Super::DoAction();
	CheckFalse(Datas.Num() > 0);

	if (bCanCombo == true)
	{
		bCanCombo = false;
		bSucceed = true;
		return;
	}

	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();

	CheckFalse(bSucceed);
	bSucceed = false;

	OwnerCharacter->StopAnimMontage();

	ComboCount++;
	ComboCount = FMath::Clamp(ComboCount, 0, Datas.Num() - 1);

	OwnerCharacter->PlayAnimMontage(Datas[ComboCount].AnimMontage, Datas[ComboCount].PlayRate, Datas[ComboCount].StartSection);
	Datas[ComboCount].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	OwnerCharacter->StopAnimMontage();
	ComboCount = 0;

	State->SetIdleMode();
	Status->SetMove();
}

void ACDoAction_Melee::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentBeginOverlap(InAttacker, InCauser, InOtherCharacter);

	// Add HittedCharacter
	int32  HittedCharactersNum = HittedCharacters.Num();
	HittedCharacters.AddUnique(InOtherCharacter);

	// HitStop
	float hitStop = Datas[ComboCount].HitStop;
	if (FMath::IsNearlyZero(hitStop) == false)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 2e-2f);
		UKismetSystemLibrary::K2_SetTimer(this, "RestoreGlobalTimeDilation", hitStop * 2e-2f, false);
	}

	// Play Particle
	UParticleSystem* hitEffect = Datas[ComboCount].Effect;
	if (hitEffect != nullptr)
	{
		FTransform transform = Datas[ComboCount].EffectTransform;
		transform.AddToTranslation(InOtherCharacter->GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, transform);
	}

	// Camera Shake
	TSubclassOf<UCameraShake> shake = Datas[ComboCount].ShakeClass;
	if (shake != nullptr)
	{
		APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		controller->PlayerCameraManager->PlayCameraShake(shake);
	}

	if (HittedCharactersNum < HittedCharacters.Num())
	{
		// TakeDamage
		FDamageEvent e;
		InOtherCharacter->TakeDamage(Datas[ComboCount].Power, e, InAttacker->GetController(), InCauser);
	}
}

void ACDoAction_Melee::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InCauser, ACharacter* InOtherCharacter)
{
	Super::OnAttachmentEndOverlap(InAttacker, InCauser, InOtherCharacter);
}

void ACDoAction_Melee::RestoreGlobalTimeDilation()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}