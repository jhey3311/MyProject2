// Fill out your copyright notice in the Description page of Project Settings.

#include "PointActor.h"
#include "Components/ArrowComponent.h"
#include "Components/TextRenderComponent.h"

APointActor::APointActor()
{
    PrimaryActorTick.bCanEverTick = false;

    // Create the Arrow Component
    PointHandle = CreateDefaultSubobject<UArrowComponent>(TEXT("PointHandle"));

    // Set the Arrow as the Root Component
    RootComponent = PointHandle;

    // Create the Text Render Component to display the score
    ScoreText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScoreText"));
    ScoreText->SetupAttachment(RootComponent);

    // Configurar el texto inicial
    PointScore = 0;
    ScoreText->SetText(FText::FromString(FString::Printf(TEXT("%d"), PointScore)));

    // Configurar tamaño y color del texto
    ScoreText->SetTextRenderColor(FColor::Yellow);
    ScoreText->SetWorldSize(40.0f);
    ScoreText->SetHorizontalAlignment(EHTA_Center);
    ScoreText->SetVerticalAlignment(EVRTA_TextCenter);
}