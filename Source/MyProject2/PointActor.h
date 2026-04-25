// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointActor.generated.h"

// Forward declaration
class UArrowComponent;
class UTextRenderComponent;

UCLASS()
class MYPROJECT2_API APointActor : public AActor
{
	GENERATED_BODY()
	
public:
    APointActor();

    // The visual handle that makes it clickable in the Editor
    UPROPERTY(VisibleAnywhere, Category = "Reference")
    UArrowComponent* PointHandle;

    // Componente para mostrar el puntaje visualmente en el mapa
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scoring")
    UTextRenderComponent* ScoreText;

    // Puntaje visible en cada punto
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
    int32 PointScore;
};
