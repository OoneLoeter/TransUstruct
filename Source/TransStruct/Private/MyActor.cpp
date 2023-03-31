// Fill out your copyright notice in the Description page of Project Settings.



#include "TransStruct/Public/MyActor.h"
#include "Runtime/Core/Public/Containers/Map.h"
#include "CoreMinimal.h"
#include "UObject/TextProperty.h"



// Sets default values


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
	//iteration for every Property
	for (TFieldIterator<const FProperty> I(StructDef); I; ++I)
	{
		const FProperty* Property = *I;

		if (Property->HasAnyPropertyFlags(CPF_Edit | CPF_EditConst | CPF_DisableEditOnInstance))
		{
			continue;
		}

		FString Key = Property->GetName();
		// FString Value = Property->GetCPPType();

		FString Value;
		Property->ExportTextItem(Value, Property->ContainerPtrToValuePtr<uint8>(Structptr), nullptr, nullptr, PPF_None);

		Result.Add(Key, Value);
	}

	return Result;

	
}

void AMyActor::MapToStruct(const TMap<FString, FString>& Map,  UStruct* StructDefinition)
{
	void* StructPtr = FMemory::Malloc(StructDefinition->GetStructureSize());
	StructDefinition->InitializeStruct(StructPtr);
	for (TFieldIterator< FProperty> PropertyIt(StructDefinition); PropertyIt; ++PropertyIt)
	{
		 FProperty* Property = *PropertyIt;
		 FString ValueStringPtr = *Map.Find(Property->GetName());
		
			void* ValuePtr = Property->ContainerPtrToValuePtr<uint8>(StructPtr);
			FString ValueString = *ValueStringPtr;
			Property->ImportText(*ValueString, ValuePtr, PPF_None, nullptr);
			//Property->ImportText_InContainer(*ValueString,ValuePtr,)
		
	}
	
}

void AMyActor::MapToStructBP(FMyStruct TargetStruct, const TMap<FString, FString>& Map)
{
	
	MapToStruct(Map,TargetStruct.StaticStruct());
}

TMap<FString, FString> AMyActor::StructToMapBP()
{
	TestStruct.F = "Sfss";
	TestStruct.b = true;
	return StructToMap(&TestStruct,TestStruct.StaticStruct());
}






//
// FMyStruct ConvertMapToStruct(const TMap<FString, FString>& Map)
// {
// 	FMyStruct Result;
//
// 	// Получаем список свойств структуры
// 	const UStruct* Struct = FMyStruct::StaticStruct();
// 	const TMap<FName, FProperty*>& Properties = Struct->GetPropertiesMap();
//
// 	// Проходим по списку свойств и конвертируем значения из TMap в свойства структуры
// 	for (const auto& Entry : Properties)
// 	{
// 		const FName& PropertyName = Entry.Key;
// 		const FProperty* Property = Entry.Value;
//
// 		
// 			// Получаем значение из TMap и конвертируем его в соответствующий тип данных
// 			const FString& ValueString = Map.FindRef(PropertyName.ToString());
// 			void* ValuePtr = Property->ContainerPtrToValuePtr<void>((void*)&Result);
// 			
// 			Property->ImportTextItem(*ValueString, ValuePtr, PPF_None, nullptr);
// 		
// 	}
//
// 	return Result;
// }