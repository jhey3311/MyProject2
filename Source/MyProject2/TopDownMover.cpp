// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownMover.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ATopDownMover::ATopDownMover()
{

    // Set this pawn to call Tick() every frame
    PrimaryActorTick.bCanEverTick = true;


    AutoPossessPlayer = EAutoReceiveInput::Player0;


    // Initialize the visual component
    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    // --- NEW CODE: Find and assign the Cube ---
    // We use ConstructorHelpers to find the asset path of the default Engine cube
    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

    // Check if we successfully found the asset to prevent crashes
    if (CubeMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(CubeMeshAsset.Object);
    }
    // ------------------------------------------

    // Set default values for our editor variables
    Velocity = 400.0f;
    MoveDirection = EMoveDirection::Right;
    bIsMoving = false;
}

// Called when the game starts or when spawned
void ATopDownMover::BeginPlay()
{
    Super::BeginPlay();
    if (GEngine)
    {
        // Parameters: Key (-1 adds a new message), Time to display, Color, and the String
        GEngine->AddOnScreenDebugMessage(
            -1,
            5.0f,
            FColor::Yellow,
            FString::Printf(TEXT("Starting the game"))
        );
    }

    // 2. Print to the Output Log (Window > Output Log)
    UE_LOG(LogTemp, Warning, TEXT("Starting the game"));
}

// Called every frame
void ATopDownMover::Tick(float DeltaTime)
{
    //Super::Tick(DeltaTime);
    Super::Tick(DeltaTime);

    // 4. Movement Logic
    if (bIsMoving)
    {
        FVector CurrentLocation = GetActorLocation();
        FVector MovementStep = FVector::ZeroVector;

        // Map the Enum to Unreal's top-down coordinate system
        // Looking straight down: +X is Up, -X is Down, +Y is Right, -Y is Left
        switch (MoveDirection)
        {
        case EMoveDirection::Up:
            MovementStep.X = 1.0f;
            break;
        case EMoveDirection::Down:
            MovementStep.X = -1.0f;
            break;
        case EMoveDirection::Right:
            MovementStep.Y = 1.0f;
            break;
        case EMoveDirection::Left:
            MovementStep.Y = -1.0f;
            break;
        
        // NUEVAS DIRECCIONES DIAGONALES:
        case EMoveDirection::UpRight:
            MovementStep.X = 1.0f;   // Up
            MovementStep.Y = 1.0f;   // Right
            break;
        case EMoveDirection::UpLeft:
            MovementStep.X = 1.0f;   // Up
            MovementStep.Y = -1.0f;  // Left
            break;
        case EMoveDirection::DownRight:
            MovementStep.X = -1.0f;  // Down
            MovementStep.Y = 1.0f;   // Right
            break;
        case EMoveDirection::DownLeft:
            MovementStep.X = -1.0f;  // Down
            MovementStep.Y = -1.0f;  // Left
            break;
        default:
            MovementStep = FVector::ZeroVector;
            break;
        }

    // Normalizar para movimiento uniforme en diagonales (importante!)
    if (MovementStep.Size() > 1.0f)
    {
        MovementStep.Normalize();
    }
        // Calculate the new position ensuring frame-rate independence using DeltaTime
        CurrentLocation += MovementStep * Velocity * DeltaTime;

        SetActorLocation(CurrentLocation);
    }

}

// Called to bind functionality to input
void ATopDownMover::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    //Super::SetupPlayerInputComponent(PlayerInputComponent);
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 5. Bind the Spacebar to trigger our ToggleMovement function
    //PlayerInputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &ATopDownMover::ToggleMovement);



}

void ATopDownMover::ToggleMovement()
{
    // Invert the boolean state
    bIsMoving = !bIsMoving;

    // 1. Print directly to the Game Screen
    if (GEngine)
    {
        // Parameters: Key (-1 adds a new message), Time to display, Color, and the String
        GEngine->AddOnScreenDebugMessage(
            -1,
            5.0f,
            FColor::Yellow,
            FString::Printf(TEXT("Spacebar Pressed! bIsMoving is now: %s"), bIsMoving ? TEXT("TRUE") : TEXT("FALSE"))
        );
    }

    // 2. Print to the Output Log (Window > Output Log)
    UE_LOG(LogTemp, Warning, TEXT("Spacebar Action Listened."));
}