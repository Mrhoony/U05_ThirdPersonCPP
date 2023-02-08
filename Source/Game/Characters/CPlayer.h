#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/CStateComponent.h"
#include "ICharacter.h"

#include "CPlayer.generated.h"

UCLASS()
class GAME_API ACPlayer : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

private:
	//SceneComponent
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

	//ActorComponent
	UPROPERTY(VisibleDefaultsOnly)
		class UCStatusComponent* Status;

	UPROPERTY(VisibleDefaultsOnly)
		class UCOptionComponent* Option;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UCStateComponent* State;

	UPROPERTY(VisibleDefaultsOnly)
		class UCMontagesComponent* Montages;

	UPROPERTY(VisibleDefaultsOnly)
		class UCActionComponent* Action;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

	void OnFist();
	void OnOneHand();
	void OnTwoHand();
	void OnMagicBall();
	void OnWarp();

	void OnDoAction();

	void OnAim();
	void OffAim();

private:
	void Begin_Roll();
	void Begin_BackStep();

public:
	void End_Roll();
	void End_BackStep();

	virtual void ChangeColor(FLinearColor InColor);

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;
};
