#include "Enemy.h"
#include "PointActor.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AEnemy::AEnemy()
{
    // Habilitamos el Tick para que pueda actualizar su posición en cada frame
    PrimaryActorTick.bCanEverTick = true;

    // 1. Configuramos la Malla
    EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
    RootComponent = EnemyMesh;

    // Opcional: Cargamos la forma básica de un cono (pirámide) que viene por defecto en el motor.
    static ConstructorHelpers::FObjectFinder<UStaticMesh> ConeAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cone.Cone'"));
    if (ConeAsset.Succeeded())
    {
        EnemyMesh->SetStaticMesh(ConeAsset.Object);
    }

    // 2. Valores por defecto
    MovementSpeed = 300.0f;
    TargetPoint = nullptr;
    CurrentPointIndex = 0;
}

void AEnemy::BeginPlay()
{
    Super::BeginPlay();

    // Si hay puntos de patrulla asignados, seleccionamos el primero
    if (PatrolPoints.Num() > 0)
    {
        CurrentPointIndex = 0;
        TargetPoint = PatrolPoints[CurrentPointIndex];
    }
}

void AEnemy::ChangeMeshForCurrentPoint()
{
    // Verificar que el índice sea válido en el array de mallas
    if (MeshesForPatrolPoints.IsValidIndex(CurrentPointIndex) && MeshesForPatrolPoints[CurrentPointIndex])
    {
        EnemyMesh->SetStaticMesh(MeshesForPatrolPoints[CurrentPointIndex]);
    }
}

void AEnemy::AdvanceToNextPoint()
{
    if (PatrolPoints.Num() == 0)
    {
        TargetPoint = nullptr;
        return;
    }

    CurrentPointIndex = (CurrentPointIndex + 1) % PatrolPoints.Num();
    TargetPoint = PatrolPoints[CurrentPointIndex];
}

void AEnemy::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Si tenemos un objetivo asignado, procedemos a movernos
    if (TargetPoint != nullptr)
    {
        FVector CurrentLocation = GetActorLocation();
        FVector TargetLocation = TargetPoint->GetActorLocation();

        // Verificamos la distancia para evitar que el objeto "tiemble" al llegar al punto exacto
        float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);

        if (DistanceToTarget > 5.0f)
        {
            // 1. Obtener el vector dirección: (Destino - Origen) y normalizarlo (longitud = 1)
            FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();

            // 2. Calcular la nueva posición (Velocidad * Tiempo)
            FVector NewLocation = CurrentLocation + (Direction * MovementSpeed * DeltaTime);

            // 3. Aplicar el movimiento
            SetActorLocation(NewLocation);
        }
        else
        {
            // Llegó al punto actual; cambiar la malla según el punto actual
            ChangeMeshForCurrentPoint();
            
            // Luego avanzar al siguiente punto
            AdvanceToNextPoint();
        }
    }
    else
    {
        // Si no hay TargetPoint pero sí PatrolPoints, inicializamos uno
        if (PatrolPoints.Num() > 0)
        {
            CurrentPointIndex = 0;
            TargetPoint = PatrolPoints[CurrentPointIndex];
        }
    }
}