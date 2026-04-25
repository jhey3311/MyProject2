#include "BallScaler.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

ABallScaler::ABallScaler()
{
    // Ensure the actor updates every frame so we can animate the scale
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    RootComponent = MeshComponent;

    // Automatically find and assign the default Unreal Engine Sphere
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
    if (SphereMeshAsset.Succeeded())
    {
        MeshComponent->SetStaticMesh(SphereMeshAsset.Object);
    }

    // Default values: Grow by 0.5 units on all axes every second
    ScaleRate = FVector(0.5f, 0.5f, 0.5f);
    bIsScaling = false; // Starts dormant
}

void ABallScaler::BeginPlay()
{
    Super::BeginPlay();

    // 1. Get the local player controller
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        // 2. Safely push this Actor onto the input stack
        EnableInput(PC);

        // 3. Bind the 'I' key action and force it to bubble down to other instances
        if (InputComponent)
        {
            InputComponent->BindAction("ToggleScale", IE_Pressed, this, &ABallScaler::ToggleScaling).bConsumeInput = false;
        }
    }
}

void ABallScaler::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 4. The Scaling Math
    if (bIsScaling)
    {
        // Get the current size
        FVector CurrentScale = GetActorScale3D();

        // Add the growth rate, made frame-rate independent using DeltaTime
        CurrentScale += ScaleRate * DeltaTime;

        // Apply the new size
        SetActorScale3D(CurrentScale);
    }
}

void ABallScaler::ToggleScaling()
{
    // Invert the boolean
    bIsScaling = !bIsScaling;

    // Print a log to the screen so we know the 'I' key was registered
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1,
            2.0f,
            FColor::Cyan,
            FString::Printf(TEXT("Scaling toggled! bIsScaling: %s"), bIsScaling ? TEXT("TRUE") : TEXT("FALSE"))
        );
    }
}