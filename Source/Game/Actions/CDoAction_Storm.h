// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actions/CDoAction.h"
#include "CDoAction_Storm.generated.h"

UCLASS()
class GAME_API ACDoAction_Storm : public ACDoAction
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void DoAction();
	virtual void Begin_DoAction();
	virtual void End_DoAction();

	virtual void Abort();

private:
	UFUNCTION()
		void DamageToHittedCharacters();

	UFUNCTION()
		void Finish();

private:
	virtual void OnAttachmentBeginOverlap(class ACharacter* InAttacker, class AActor* Causer, class ACharacter* InOtherCharacter) override;
	virtual void OnAttachmentEndOverlap(class ACharacter* InAttacker, class AActor* Causer, class ACharacter* InOtherCharacter) override;

private:
	UPROPERTY(EditDefaultsOnly)
		float DPS = 0.1f;

	UPROPERTY(EditDefaultsOnly)
		float ActiveTime = 5.0f;

	UPROPERTY(EditDefaultsOnly)
		float AroundSpeed = 300.f;

	UPROPERTY(EditDefaultsOnly)
		float Radius = 150.f;

	UPROPERTY(VisibleDefaultsOnly)
		class UParticleSystemComponent* Particle;

private:
	class UBoxComponent* Box;
	bool bActivating;

	TArray<class ACharacter*> HittedCharacters;
	float YawAngle;
};
