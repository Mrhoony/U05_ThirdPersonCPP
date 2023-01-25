#include "Characters/CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateSceneComponent(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateSceneComponent(this, &Camera, "Camera", SpringArm);

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	USkeletalMesh* meshAsset;
	CHelpers::GetAsset<USkeletalMesh>(&meshAsset, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(meshAsset);

	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	bUseControllerRotationYaw = false;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
}

void ACPlayer::OnMoveForward(float InAxis)
{
}

void ACPlayer::OnMoveRight(float InAxis)
{
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
}

void ACPlayer::OnVerticalLook(float InAxis)
{
}
