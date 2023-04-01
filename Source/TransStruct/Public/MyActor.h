// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"


UENUM(BlueprintType)
enum class ETest :uint8
{
	Idle = 0 UMETA(DisplayName = "Idle", Value = 0),
	Walk = 1 UMETA(DisplayName = "Walk", Value = 1),
	Jog = 2 UMETA(DisplayName = "Jog", Value = 2),
	SpeedRun = 3 UMETA(DisplayName = "SpeedRun", Value = 3),
};



USTRUCT(BlueprintType)
struct FMyStruct
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite)
	ETest D;

	UPROPERTY(BlueprintReadWrite)
	FString F;

	UPROPERTY(BlueprintReadWrite)
	bool b;

	


};
UCLASS()
class TRANSSTRUCT_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMyStruct TestStruct;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FMyStruct TestOutStruct;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
	

	UFUNCTION(BlueprintCallable)
	TMap<FString, FString> StructToMapBP ();
	
	UFUNCTION(BlueprintCallable)
	void MapToStructBP (const TMap<FString, FString>& Map);
	
	void ConvertMapToStruct(const TMap<FString, FString>& Map, void* StructPtr, UStruct* StructDef);

	TMap<FString, FString> StructToMap( const void* Structprt, const UStruct* StructDefinition);
};
