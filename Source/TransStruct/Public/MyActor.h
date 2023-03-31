// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"


USTRUCT(BlueprintType)
struct FMyStruct
{
	GENERATED_BODY()
	

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

	
	
	TMap<FString, FString> StructToMap( const void* Structprt, const UStruct* StructDefinition);

	UFUNCTION(BlueprintCallable)
	TMap<FString, FString> StructToMapBP ();

	void MapToStruct( const TMap<FString, FString>& Map,  UStruct* StructDefinition);


	UFUNCTION(BlueprintCallable)
	void MapToStructBP (FMyStruct TargetStruct,const TMap<FString, FString>& Map);

	//void AMyActor::ConvertMapToStruct(const TMap<FString, FString>& Map);
};
