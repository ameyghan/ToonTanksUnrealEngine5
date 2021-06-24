# ToonTanksUnrealEngine5
 ToonTanks Modified and Optimized for Unreal Engine 5
 This version of ToonTanks has been modified for Unreal Engine 5. 

 The changes to this version: 

 1. UMatineeCameraShake has its own class so it is forward declared in all header files that need access to to remove the compiler error for pointer to incomplete class types.
 2. The header #include "UMatineeCameraShake.h" has been added to cpp files needing access to it.
 3. Additional code comments 
 4. Additional debug options about health and actor destruction. 
 
