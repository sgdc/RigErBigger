// Fill out your copyright notice in the Description page of Project Settings.

#include "RigerBigger.h"
#include "SplitscreenRemover.h"


// Sets default values
ASplitscreenRemover::ASplitscreenRemover()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASplitscreenRemover::BeginPlay()
{
	RemoveLocalSplitscreenPlayersFromGame(GetGameInstance());

	Super::BeginPlay();
	
}

// Called every frame
void ASplitscreenRemover::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Removes local splitscreen players, with Player Index 1 to 3, from the game, leaving only the primary player
void ASplitscreenRemover::RemoveLocalSplitscreenPlayersFromGame(UGameInstance* CurrentGameInstance)
{
	const int32 MaxSplitScreenPlayers = 4;
	ULocalPlayer* PlayersToRemove[MaxSplitScreenPlayers];
	int32 RemIndex = 0;

	for (FConstPlayerControllerIterator Iterator = GEngine->GameViewport->GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		// Remove only local split screen players
		APlayerController* Controller = *Iterator;
		if (Controller && Controller->IsLocalController() && !Controller->IsPrimaryPlayer())
		{
			ULocalPlayer* ExPlayer = Cast<ULocalPlayer>(Controller->Player);
			if (ExPlayer)
			{
				PlayersToRemove[RemIndex++] = ExPlayer;
				Controller->PawnPendingDestroy(Controller->GetPawn());
			}
		}
	}

	for (int32 i = 0; i < RemIndex; ++i)
	{
		//GEngine->GameViewport->RemovePlayer(PlayersToRemove[i]); // GameViewport::RemovePlayer was Deprecated in 4.4
		CurrentGameInstance->RemoveLocalPlayer(PlayersToRemove[i]);
	}
}
