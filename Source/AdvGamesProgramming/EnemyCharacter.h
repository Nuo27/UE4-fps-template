// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyCharacter.generated.h"

UENUM()
enum class AgentState : uint8
{
	PATROL,
	CHASE,
	CHECK,
	AIM,
	SEARCH
};

UCLASS()
class ADVGAMESPROGRAMMING_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	TArray <class ANavigationNode* > Path;
	ANavigationNode* CurrentNode;
	class AAIManager* Manager;

	UPROPERTY(EditAnywhere, meta=(UIMin="10.0", UIMax="1000.0", ClampMin="10.0", ClampMax="1000.0"))
	float PathfindingNodeAccuracy;

	class UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, Category = "AI")
	AgentState CurrentAgentState;

	class UAIPerceptionComponent* PerceptionComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	AActor* DetectedActor;
	bool bCanSeePlayer;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void AgentPatrol();
	void AgentChase();
	void AgentCheck();
	void AgentAim();
	void AgentSearch();

	UFUNCTION()
	void SensePlayer(AActor* ActorSensed, FAIStimulus Stimulus);

	UFUNCTION(BlueprintImplementableEvent)
	void Fire(FVector FireDirection);
	UPROPERTY(EditAnywhere)
		bool isItemExist;
	UPROPERTY(EditAnywhere)
	bool isItemChecked;
	UFUNCTION(BlueprintImplementableEvent)
		void CheckItem();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
		bool isEnemyDead;
private:

	void MoveAlongPath();

};
