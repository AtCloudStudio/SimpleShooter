# Simple Shooter
---
## Introduction
Hi, I am a beginner of indie game developer, and this is my unreal engine course project named "Simple Shooter". 

You're welcome to download and do whatever legal with all these files. Please feel free to leave your comments, that would be greatly appreciated.

---
## Game engine version: 
* Unreal Engine 4.25.1

---
## Daily Updates
### Day 01
* Imported assets. These are all Epic Unreal Engine marketplace free assets. One is "Paragon Wraith", and the other one is "Modular SciFi Season 1". 
* Created new C++ Character class ShooterCharacter and its derived blueprint class BP_ShooterCharacter
* Bound input, implenmented character moving
* Added third person camera with spring arm on shooter character

### Day 02
* Created new Animation blueprint ABP_ShooterCharacter
* Created new Blend Space blueprint BS_Locomotion and applied it to ABP_ShooterCharacter
* Applied ABP_ShooterCharacter to BP_ShooterCharacter
* Created new Actor C++ class GunBase and its derived blueprint classes BP_Rifle and BP_Launcher
* Implemented spawning new weapon and attaching it to character 
* Imported ShooterGame asset
* Added character gun muzzle flash particle
* Added gun hit impact effect
* Created new Actor Component C++ class HealthComponent, and added it to shooter character
* Implemented character taking damage
* Created new Player Controller C++ class PlayerControllerBase
* Created new Game Mode C++ class ShooterGameModeBase and its derived blueprint class BP_GameMode
* Added character dead animation
* Tried to trigger character death, bugged
