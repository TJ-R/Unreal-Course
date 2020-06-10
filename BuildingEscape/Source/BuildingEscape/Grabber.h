// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"

#define DEBUG

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
UPROPERTY(EditAnywhere)
float Reach = 250.f;

UPROPERTY()
UPhysicsHandleComponent* PhysicsHandle = nullptr;
UPROPERTY()
UInputComponent* InputComponent = nullptr;

void Grab();
void Release();
void FindPhysicsHandle();
void SetupInputComponent();

//Return the first Actor within reach with a physics body
FHitResult GetFirstPhysicsBodyInReach() const;

//Return the line trace end
FVector GetPlayerReach() const;

//Return the players location in the world
FVector GetPlayerWorldPos() const;

DEBUG void CreateDebugLine(FVector StartPos, FVector EndPos);

};
