#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ICharacter.h"
#include "Components/CStateComponent.h"
#include "Components/SlateWrapperTypes.h"
#include "CEnemy.generated.h"

UCLASS()
class GAME_API ACEnemy : public ACharacter, public IICharacter
{
	GENERATED_BODY()

public:
	ACEnemy();

	void ChangeColor(FLinearColor InColor) override;
	virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

private:
	UFUNCTION()
		void OnStateTypeChanged(EStateType InPrevType, EStateType InNewType);

	UFUNCTION()
		void RestoreLogoColor();

	void Hitted() override;
	void Dead() override;

	UFUNCTION()
		void End_Dead() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		ESlateVisibility VisibleType = ESlateVisibility::Hidden;

	UPROPERTY(EditAnywhere)
		float LaunchValue = 25.f;

	UPROPERTY(EditAnywhere)
		float DeadLaunchValue = 1e+7f;

	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* NameWidget;
	
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* HealthWidget;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly) class UCActionComponent* Action;

private:
	UPROPERTY(VisibleDefaultsOnly) class UCMontagesComponent* Montages;	
	UPROPERTY(VisibleDefaultsOnly) class UCStateComponent* State;	
	UPROPERTY(VisibleDefaultsOnly) class UCStatusComponent* Status;
	UPROPERTY(VisibleDefaultsOnly) class UCDissolveComponent* Dissolve;

private:
	class UMaterialInstanceDynamic* BodyMaterial;
	class UMaterialInstanceDynamic* LogoMaterial;

	class ACharacter* Attacker;
	class AActor* Causer;
	float DamageValue;
};
