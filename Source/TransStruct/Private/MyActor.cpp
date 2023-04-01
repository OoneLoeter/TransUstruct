// Fill out your copyright notice in the Description page of Project Settings.



#include "TransStruct/Public/MyActor.h"
#include "Runtime/Core/Public/Containers/Map.h"
#include "CoreMinimal.h"

#include "CoreMinimal.h"
#include "GameplayTagsManager.h"

#include "Engine/DataTable.h"



// Sets default values

FGameplayTag Damage_Fire;
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
}

TMap<FString, FString> AMyActor::StructToMap(const void* Structptr, const UStruct* StructDef)
{
	TMap<FString, FString> Result;
	//Итерация по каждому свойству
	for (TFieldIterator<const FProperty> I(StructDef); I; ++I)
	{
		//получаем указатель на свойства
		const FProperty* Property = *I;
		//получаем имя свойства
		FString Key = Property->GetName();
		FString Value;
		//получаем значение свойства в переменную value
		Property->ExportTextItem(Value, Property->ContainerPtrToValuePtr<uint8>(Structptr), nullptr, nullptr, PPF_None);
		Result.Add(Key, Value);
	}

	return Result;
}

void AMyActor::ConvertMapToStruct(const TMap<FString, FString>& Map,void* StructPtr, UStruct* StructDef)
{
	
	
	// Проходим по списку свойств и конвертируем значения из TMap в свойства структуры
	for (TFieldIterator< FProperty> PropertyIt(StructDef); PropertyIt; ++PropertyIt)
	{
		// Получаем значение из TMap и конвертируем его в соответствующий тип данных
		const FString& ValueString = Map.FindRef(PropertyIt->GetName());
		void* ValuePtr = PropertyIt->ContainerPtrToValuePtr<void>(StructPtr);
		//Устанавливаем значение в структуру
		PropertyIt->ImportText(*ValueString, ValuePtr, PPF_None, nullptr);
	}
}

void AMyActor::MapToStructBP( const TMap<FString, FString>& Map)
{
	
	ConvertMapToStruct(Map,&TestOutStruct, TestOutStruct.StaticStruct());
}

TMap<FString, FString> AMyActor::StructToMapBP()
{
	TestStruct.D = ETest::Jog;
	TestStruct.F = "Sfss";
	TestStruct.b = true;
	
	return StructToMap(&TestStruct,TestStruct.StaticStruct());
}







