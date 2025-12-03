// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseTrap.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrapManagement.generated.h"


//class BaseTrap; //forward declaration

UCLASS(Blueprintable) //pour afficher la classe dans l’éditeur unreal
class TEMPLE_ESCAPE_API ATrapManagement : public AActor
{
	GENERATED_BODY()

public : 
	//le pièges à spawn
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Traps", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseTrap> trapClass;

	//la liste de pieges
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Traps", meta = (AllowPrivateAccess = "true"))
	TArray<ABaseTrap*> ActiveTraps;


	
public:	
	// Sets default values for this actor's properties
	ATrapManagement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
