#include "CDoAction_Storm.h"
#include "Global.h"

#include "CAttachment.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"

#include "Components/BoxComponent.h"
#include "particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"

void ACDoAction_Storm::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* actor : OwnerCharacter->Children)
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Storm"))
		{
			Box = CHelpers::GetComponent<UBoxComponent>(actor);
			break;
		}
	}
}

void ACDoAction_Storm::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	YawAngle += AroundSpeed * DeltaTime;
	if (FMath::IsNearlyEqual(YawAngle, 360.f))
		YawAngle = 0.f;

	FVector center = OwnerCharacter->GetActorLocation();
	FVector awayFromCenter = FVector(Radius, 0, 0);
	FVector rotVector = awayFromCenter.RotateAngleAxis(YawAngle, FVector::UpVector);
	center += rotVector;

	Box->SetWorldLocation(center);
}

void ACDoAction_Storm::DoAction()
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(bActivating);

	State->SetActionMode();
	bActivating = true;

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Storm::Begin_DoAction()
{
	YawAngle = OwnerCharacter->GetActorForwardVector().Rotation().Yaw;

	// 파티클 스폰
	Particle = UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, Box, NAME_None);
	Particle->SetRelativeLocation(Datas[0].EffectTransform.GetLocation());
	Particle->SetRelativeScale3D(Datas[0].EffectTransform.GetScale3D());

	// 충돌체 켜기
	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	if (attachment != nullptr)
		attachment->OnCollisions();	

	// DPS마다 데미지를 주는 함수 타이머 생성
	UKismetSystemLibrary::K2_SetTimer(this, "DamageToHittedCharacters", DPS, true);
}

void ACDoAction_Storm::End_DoAction()
{
	Status->SetMove();
	State->SetIdleMode();

	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "Finish");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer, ActiveTime, false);
}

void ACDoAction_Storm::Abort()
{
	Finish();
}

void ACDoAction_Storm::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* Causer, ACharacter* InOtherCharacter)
{
	HittedCharacters.AddUnique(InOtherCharacter);
}

void ACDoAction_Storm::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* Causer, ACharacter* InOtherCharacter)
{
	HittedCharacters.Remove(InOtherCharacter);
}

void ACDoAction_Storm::DamageToHittedCharacters()
{
	FDamageEvent e;
	for (int32 i=0; i<HittedCharacters.Num(); i++)
	{
		UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(HittedCharacters[i]);

		bool bIgnore = false;
		bIgnore |= (state->IsDeadMode());
		bIgnore |= (HittedCharacters[i] == nullptr);
		bIgnore |= (HittedCharacters[i]->IsPendingKill());

		if (bIgnore == true) continue;

		HittedCharacters[i]->TakeDamage(Datas[0].Power, e, OwnerCharacter->GetController(), this);
	}
}

void ACDoAction_Storm::Finish()
{
	if(Particle != nullptr)
	Particle->DestroyComponent();

	bActivating = false;
	
	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	if (attachment != nullptr)
		attachment->OffCollisions();

	UKismetSystemLibrary::K2_ClearTimer(this, "DamageToHittedCharacters");
}
