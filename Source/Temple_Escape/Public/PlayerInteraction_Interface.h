// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include  "PlayerInteraction_Interface.generated.h"

/** Please add a class description */
UINTERFACE(NotBlueprintable)
class TEMPLE_ESCAPE_API UPlayerInteraction_Interface : public UInterface
{
	GENERATED_BODY()

};

class TEMPLE_ESCAPE_API IPlayerInteraction_Interface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void Interact();
};