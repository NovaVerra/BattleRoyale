// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BattleRoyaleGameMode.generated.h"

UCLASS(minimalapi)
class ABattleRoyaleGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABattleRoyaleGameMode();

	virtual void							PostLogin(APlayerController* NewPlayer) override; // population players in game

	void									PlayerDied(class ABattleRoyaleCharacter* Killed, class ABattleRoyaleCharacter* Killer);
	void									WinnerFound(class ABattleRoyalePlayerState* Winner);

	UPROPERTY(Transient) // don't save to disk
	TArray<class ABattleRoyaleCharacter*>	PlayersAlive {};
};



