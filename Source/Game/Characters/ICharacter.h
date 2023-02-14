#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ICharacter.generated.h"

UINTERFACE(MinimalAPI)
class UICharacter : public UInterface
{
	// ������ <-> �������Ʈ�� �۽ſ�
	GENERATED_BODY()
};

class GAME_API IICharacter
{
	GENERATED_BODY()

public:
	virtual void ChangeColor(FLinearColor InColor) = 0;
	virtual void Hitted() = 0;
	virtual void Dead() = 0;
};
