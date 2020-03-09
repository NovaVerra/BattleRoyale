// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleRoyaleGameState.h"
#include "Net/UnrealNetwork.h"

// Broadcast for UI to catch
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWinnerFound);

void	ABattleRoyaleGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps)
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABattleRoyaleGameState, Winner);
}

void	ABattleRoyaleGameState::OnRep_Winner()
{
	OnWinnerFound.Broadcast();
}
