# ToonTanksUnrealEngine5
 ToonTanks game modified and Optimized for Unreal Engine 5
 This version of ToonTanks has been modified for Unreal Engine 5. 

 The changes to this version: 

 1. UMatineeCameraShake has its own class so it is forward declared in all header files that need access to to remove the compiler error for pointer to incomplete class types.
 2. The header #include "UMatineeCameraShake.h" has been added to cpp files needing access to it.
 3. Removed the deprecated camera shake function and added the correct camera shake for the new version of Unreal Engine 
    GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(...);
 4. Additional code comments 
 5. Additional debug options about health and actor destruction. 
 6. Batch files for advanced debugging and easy access. 
 
