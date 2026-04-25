// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

// Declaración adelantada de la clase que creamos anteriormente
class APointActor;

UCLASS()
class MYPROJECT2_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Componente visual para la malla
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visual")
    UStaticMeshComponent* EnemyMesh;

    // Lista de puntos de patrulla (A, B, C, ...)
    // EditInstanceOnly: se asignan por instancia en el nivel
    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement")
    TArray<APointActor*> PatrolPoints;

    // Lista de mallas correspondientes a cada punto de patrulla
    // Índice 0 = malla para punto A, índice 1 = malla para punto B, etc.
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual")
    TArray<UStaticMesh*> MeshesForPatrolPoints;

    // Índice del punto objetivo actual dentro de PatrolPoints
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    int32 CurrentPointIndex;

    // Velocidad de movimiento en unidades de Unreal (cm) por segundo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float MovementSpeed;

    // Puntero al actor objetivo actual (sin editar directamente en editor, se gestiona por la lógica)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
    APointActor* TargetPoint;

    // Set de puntos recolectados del Enemy
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scoring")
    TSet<int32> Puntos;

    // Array de puntos visitados
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scoring")
    TArray<APointActor*> VisitedPoints;

private:
    // Avanza al siguiente punto de patrulla (cíclico)
    void AdvanceToNextPoint();

    // Cambia la malla según el índice del punto actual
    void ChangeMeshForCurrentPoint();
};
