#include "CDoAction_Warp.h"
#include "Global.h"

#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Actions/CAttachment.h"

#include "GameFramework/Character.h"
#include "Components/DecalComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

void ACDoAction_Warp::BeginPlay()
{
	Super::BeginPlay();

	for (AActor* child : OwnerCharacter->Children)
	{
		if (child->IsA<ACAttachment>() && child->GetActorLabel().Contains("Warp"))
		{
			Decal = CHelpers::GetComponent<UDecalComponent>(child);
			SkelMesh = CHelpers::GetComponent<USkeletalMeshComponent>(child);
			StaticMesh = CHelpers::GetComponent<UStaticMeshComponent>(child);

			break;
		}
	}
}

void ACDoAction_Warp::DoAction()
{
	CheckFalse(State->IsIdleMode());

	FRotator rotation;
	CheckFalse(GetCursorLocationAndRotation(Location, rotation));

	State->SetActionMode();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Warp::Begin_DoAction()
{
	FTransform transform = Datas[0].EffectTransform;

	UGameplayStatics::SpawnEmitterAttached
	(
		Datas[0].Effect,
		OwnerCharacter->GetMesh(),
		"",
		transform.GetLocation(),
		FRotator(transform.GetRotation()),
		transform.GetScale3D()
	);
}

void ACDoAction_Warp::End_DoAction()
{
	State->SetIdleMode();
	Status->SetMove();

	Location.Z += OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
	OwnerCharacter->SetActorLocation(Location, true);
	Location = FVector::ZeroVector;
}

void ACDoAction_Warp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckFalse(*bEquipped);

	FVector location;
	FRotator rotation;
	if (GetCursorLocationAndRotation(location, rotation) == true)
	{
		FRotator ownerRotator = OwnerCharacter->GetController<APlayerController>()->GetControlRotation();
		ownerRotator.Yaw += 90.f;
		ownerRotator.Roll = 0.f;
		ownerRotator.Pitch = 0.f;

		Decal->SetVisibility(true);
		Decal->SetWorldLocation(location);
		Decal->SetWorldRotation(rotation);

		SkelMesh->SetVisibility(true);
		SkelMesh->SetWorldLocation(location);
		SkelMesh->SetWorldRotation(ownerRotator);

		StaticMesh->SetVisibility(true);
		StaticMesh->SetWorldLocation(location);
		StaticMesh->SetWorldRotation(ownerRotator);
	}
	else
	{
		Decal->SetVisibility(false);
		SkelMesh->SetVisibility(false);
		StaticMesh->SetVisibility(false);
	}
}

bool ACDoAction_Warp::GetCursorLocationAndRotation(FVector& OutLocation, FRotator& OutRotator)
{
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Add(EObjectTypeQuery::ObjectTypeQuery1);

	FHitResult hitResult;
	if (controller->GetHitResultUnderCursorForObjects(objects, false, hitResult))
	{
		OutLocation = hitResult.Location;
		OutRotator = hitResult.ImpactNormal.Rotation();
		return true;
	}

	return false;
}
