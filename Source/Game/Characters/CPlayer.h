#pragma once

#include "CoreMinimal.h"

#include "Components/CStateComponent.h"
#include "ICharacter.h"

#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"

#include "CPlayer.generated.h"

UCLASS()
class GAME_API ACPlayer : public ACharacter, public IICharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	FGenericTeamId GetGenericTeamId() const override;

	FORCEINLINE class UCUserWidget_ActionContainer* GetActionContainerWidget() { return ActionContainerWidget; }

public:
	void End_Roll();
	void End_BackStep();

	virtual void ChangeColor(FLinearColor InColor);

public:
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Hitted() override;
	virtual void Dead() override;
	virtual void End_Dead() override;

private:
	UFUNCTION() void OnFist();
	UFUNCTION() void OnOneHand();
	UFUNCTION() void OnTwoHand();
	UFUNCTION() void OnMagicBall();
	UFUNCTION() void OnWarp();
	UFUNCTION() void OnStorm();

private:
	//Axis Mapping
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);
	void OnZoom(float InAxis);

	//Action Mapping
	void OnEvade();
	void OnWalk();
	void OffWalk();

	void OnDoAction();

	void OnAim();
	void OffAim();

	void OnActionSwitch();
	void OffActionSwitch();

private:
	void Begin_Roll();
	void Begin_BackStep();

	void BindActionItem();

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UPROPERTY(EditDefaultsOnly)
		uint8 TeamID = 0;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class UCUserWidget_ActionContainer> ActionContainerWidgetClass;

private:
	//SceneComponent
	UPROPERTY(VisibleDefaultsOnly)		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly)		class UCameraComponent* Camera;

	//ActorComponent
	UPROPERTY(VisibleDefaultsOnly)		class UCStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly)		class UCOptionComponent* Option;
	UPROPERTY(VisibleDefaultsOnly)		class UCStateComponent* State;
	UPROPERTY(VisibleDefaultsOnly)		class UCMontagesComponent* Montages;
	UPROPERTY(VisibleDefaultsOnly)		class UCActionComponent* Action;

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue;

	class UCUserWidget_ActionContainer* ActionContainerWidget;
};
