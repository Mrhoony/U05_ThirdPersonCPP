#include "Characters/CPlayer.h"
#include "Global.h"
#include "Components/CStatusComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CActionComponent.h"
#include "Widgets/CUserWidget_ActionContainer.h"
#include "Widgets/CUserWidget_ActionItem.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/CapsuleComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//Create SceneComponent
	CHelpers::CreateSceneComponent(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateSceneComponent(this, &Camera, "Camera", SpringArm);

	//Create ActorComponent
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &Montages, "Montages");
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &Option, "Option");
	CHelpers::CreateActorComponent(this, &State, "State");

	//Component Settings
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	
	USkeletalMesh* meshAsset;
	CHelpers::GetAsset<USkeletalMesh>(&meshAsset, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(meshAsset);

	TSubclassOf<UAnimInstance> animInstanceClass;
	CHelpers::GetClass<UAnimInstance>(&animInstanceClass, "AnimBlueprint'/Game/Player/ABP_CPlayer.ABP_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstanceClass);

	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	//Movment Settings
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = Status->GetRunSpeed();
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;

	// UI ActionWidget
	CHelpers::GetClass<UCUserWidget_ActionContainer>(&ActionContainerWidgetClass, "/Game/Widgets/WB_ActionContainer");
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	// Create Dynamic Material
	UMaterialInstanceConstant* bodyMaterial;
	UMaterialInstanceConstant* logoMaterial;

	CHelpers::GetAssetDynamic(&bodyMaterial, "MaterialInstanceConstant'/Game/Character/Materials/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'");
	CHelpers::GetAssetDynamic(&logoMaterial, "MaterialInstanceConstant'/Game/Character/Materials/M_UE4Man_ChestLogo_Inst.M_UE4Man_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(bodyMaterial, nullptr);
	LogoMaterial = UMaterialInstanceDynamic::Create(logoMaterial, nullptr);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	State->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);

	Action->SetUnaremdMode();

	// Create UI
	ActionContainerWidget = CreateWidget<UCUserWidget_ActionContainer, APlayerController>(Cast<APlayerController>(GetController()), ActionContainerWidgetClass);
	ActionContainerWidget->AddToViewport();
	ActionContainerWidget->SetVisibility(ESlateVisibility::Hidden);

	BindActionItem();
}

void ACPlayer::BindActionItem()
{
	ActionContainerWidget->GetItem("Item1")->OnActionItemSelected.AddDynamic(this, &ACPlayer::OnFist);
	ActionContainerWidget->GetItem("Item2")->OnActionItemSelected.AddDynamic(this, &ACPlayer::OnOneHand);
	ActionContainerWidget->GetItem("Item3")->OnActionItemSelected.AddDynamic(this, &ACPlayer::OnTwoHand);
	ActionContainerWidget->GetItem("Item4")->OnActionItemSelected.AddDynamic(this, &ACPlayer::OnMagicBall);
	ActionContainerWidget->GetItem("Item5")->OnActionItemSelected.AddDynamic(this, &ACPlayer::OnWarp);
	ActionContainerWidget->GetItem("Item6")->OnActionItemSelected.AddDynamic(this, &ACPlayer::OnStorm);
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FGenericTeamId ACPlayer::GetGenericTeamId() const
{
	return FGenericTeamId(TeamID);
}

void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Roll:		Begin_Roll();			break;
		case EStateType::BackStep:	Begin_BackStep();		break;
		case EStateType::Hitted:	Hitted();				break;
		case EStateType::Dead:		Dead();					break;
	}
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPlayer::OnZoom);

	PlayerInputComponent->BindAction("Evade", EInputEvent::IE_Pressed, this, &ACPlayer::OnEvade);
	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Pressed, this, &ACPlayer::OnWalk);
	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Released, this, &ACPlayer::OffWalk);

	PlayerInputComponent->BindAction("Fist", EInputEvent::IE_Pressed, this, &ACPlayer::OnFist);
	PlayerInputComponent->BindAction("OneHand", EInputEvent::IE_Pressed, this, &ACPlayer::OnOneHand);
	PlayerInputComponent->BindAction("TwoHand", EInputEvent::IE_Pressed, this, &ACPlayer::OnTwoHand);
	PlayerInputComponent->BindAction("MagicBall", EInputEvent::IE_Pressed, this, &ACPlayer::OnMagicBall);
	PlayerInputComponent->BindAction("Warp", EInputEvent::IE_Pressed, this, &ACPlayer::OnWarp);
	PlayerInputComponent->BindAction("Storm", EInputEvent::IE_Pressed, this, &ACPlayer::OnStorm);
		
	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &ACPlayer::OnDoAction);
	
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);
	
	PlayerInputComponent->BindAction("ActionSwitch", EInputEvent::IE_Pressed, this, &ACPlayer::OnActionSwitch);
	PlayerInputComponent->BindAction("ActionSwitch", EInputEvent::IE_Released, this, &ACPlayer::OffActionSwitch);
}

void ACPlayer::OnMoveForward(float InAxis)
{
	CheckFalse(Status->IsCanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnMoveRight(float InAxis)
{
	CheckFalse(Status->IsCanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	float rate = Option->GetHorizontalLookRate();
	AddControllerYawInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	float rate = Option->GetVerticalLookRate();
	AddControllerPitchInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnZoom(float InAxis)
{
	SpringArm->TargetArmLength += Option->GetZoomSpeed()* InAxis* GetWorld()->GetDeltaSeconds();
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, Option->GetZoomRange().X, Option->GetZoomRange().Y);
}

void ACPlayer::OnEvade()
{
	CheckFalse(State->IsIdleMode());
	CheckFalse(Status->IsCanMove());

	if (InputComponent->GetAxisValue("MoveForward") < 0.f)
	{
		State->SetBackStepMode();
		return;
	}

	State->SetRollMode();
}

void ACPlayer::OnWalk() { GetCharacterMovement()->MaxWalkSpeed = Status->GetWalkSpeed(); }
void ACPlayer::OffWalk(){	GetCharacterMovement()->MaxWalkSpeed = Status->GetRunSpeed();}

void ACPlayer::OnFist()
{
	CheckFalse(State->IsIdleMode());

	Action->SetFistMode();
}
void ACPlayer::OnOneHand()
{
	CheckFalse(State->IsIdleMode());

	Action->SetOneHandMode();
}
void ACPlayer::OnTwoHand()
{
	CheckFalse(State->IsIdleMode());

	Action->SetTwoHandMode();
}
void ACPlayer::OnMagicBall() { Action->SetMagicBallMode(); }
void ACPlayer::OnWarp() { Action->SetWarpMode(); }
void ACPlayer::OnStorm() { Action->SetStormMode(); }

void ACPlayer::OnDoAction() { Action->DoAction(); }
void ACPlayer::OnAim() { Action->DoOnAim(); }
void ACPlayer::OffAim() { Action->DoOffAim(); }

void ACPlayer::OnActionSwitch()
{
	CheckFalse(State->IsIdleMode());

	ActionContainerWidget->SetVisibility(ESlateVisibility::Visible);
	GetController<APlayerController>()->bShowMouseCursor = true;
	GetController<APlayerController>()->SetInputMode(FInputModeGameAndUI());
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f);
}

void ACPlayer::OffActionSwitch()
{
	ActionContainerWidget->SetVisibility(ESlateVisibility::Hidden);
	GetController<APlayerController>()->bShowMouseCursor = false;
	GetController<APlayerController>()->SetInputMode(FInputModeGameOnly());
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}

void ACPlayer::Begin_Roll()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	FVector start = GetActorLocation();
	FVector target = start + GetVelocity().GetSafeNormal2D();
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));

	Montages->PlayRoll();
}

void ACPlayer::Begin_BackStep()
{
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	Montages->PlayBackStep();
}

void ACPlayer::End_Roll()
{
	if (Action->IsUnaremdMode() == false)
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	State->SetIdleMode();
}

void ACPlayer::End_BackStep()
{
	if (Action->IsUnaremdMode() == true)
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	
	State->SetIdleMode();
}

void ACPlayer::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

float ACPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	DamageValue = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	Causer = DamageCauser;
	Attacker = Cast<ACharacter>(EventInstigator->GetPawn());

	Action->AbortByDamaged();

	Status->DecreaseHealth(DamageValue);

	if (Status->GetHealth() <= 0.f)
	{
		State->SetDeadMode();
		return DamageValue;
	}

	State->SetHittedMode();

	return DamageValue;
}

void ACPlayer::Hitted()
{
	// Play Hit Montage
	Montages->PlayHitted();
	Status->SetMove();
}

void ACPlayer::Dead()
{
	CheckFalse(State->IsDeadMode());

	// All Weapon Collision Disable
	Action->Dead();

	// Play Dead Montage
	Montages->PlayDead();

	GetCapsuleComponent()->SetCollisionProfileName("Spectator");
}

void ACPlayer::End_Dead()
{
	Action->End_Dead();

	UKismetSystemLibrary::QuitGame(GetWorld(), GetController<APlayerController>(), EQuitPreference::Quit, false);
}
