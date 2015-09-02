// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SplitscreenRemover.generated.h"

UCLASS()
class RIGERBIGGER_API ASplitscreenRemover : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplitscreenRemover();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Removes local splitscreen players, with Player Index 1 to 3, from the game, leaving only the primary player
	UFUNCTION(BlueprintCallable, Category = "Multiplayer")
		static void RemoveLocalSplitscreenPlayersFromGame(UGameInstance* CurrentGameInstance);
	
};
