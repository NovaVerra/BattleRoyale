// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BattleRoyaleGameState.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYALE_API ABattleRoyaleGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void	GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const override;
	
	/* The winner of the match */
	UPROPERTY(ReplicatedUsing = OnRep_Winner, Transient, BlueprintReadOnly, Category="Game State")
	class ABattleRoyalePlayerState*	Winner = nullptr;

	UFUNCTION()
	void			OnRep_Winner();
};
