#include "TobiiEyeTracking/Public/ITobiiEyeTracker.h"
#include "GameFramework/Actor.h"

class EyeTrackingExample : public AActor
{
    void Tick(float DeltaTime) override
    {
        Super::Tick(DeltaTime);
        
        // Check if Tobii eye tracker is available and connected
        ITobiiEyeTracker* TobiiEyeTracker = ITobiiEyeTracker::GetEyeTracker();
        if (TobiiEyeTracker && TobiiEyeTracker->IsConnected())
        {
            // Get the gaze ray from Tobii eye tracker
            FVector WorldGazeOrigin;
            FVector WorldGazeDirection;
            TobiiEyeTracker->GetCombinedGazeData(WorldGazeOrigin, WorldGazeDirection);
            
            // Perform actions based on gaze direction
            // For example, move an object with the gaze direction:
            FHitResult HitResult;
            GetWorld()->LineTraceSingleByChannel(HitResult, WorldGazeOrigin, WorldGazeOrigin + WorldGazeDirection * 10000.f, ECC_Visibility);
            if (HitResult.bBlockingHit)
            {
                SetActorLocation(HitResult.ImpactPoint);
            }
        }
    }
};
