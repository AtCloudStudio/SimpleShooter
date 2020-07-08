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
* Tried to trigger character death animation, bugged

### Day 03
* Code refactored, whole game architecture rebuilt
* Abandoned the Gun system, as a component, directly attached guns to character mesh instead 
* Created C++ derived classes PlayerShooter and EnemyShooter based on ShooterCharacter
* Created new blueprints based on the above classes: BP_PlayerShooter and BP_EnemyShooter
* Created new C++ Actor class ProjectileBase and its derived blueprint class BP_Projectile
* Implemented character movement system, shooting system, character health system, and death trigger

### Day 04
* Created new C++ AIController class AIContorllerBase and its derived blueprint class BP_ShooterAIController, and applied it to BP_EnemyShooter
* Created Behavior Tree BT_EnemyAI and Blackboard BB_EnemyAI, linked and applied them to BP_ShooterAIController 
* Created new C++ BTTask_BlackboardBase class BTTask_ClearBlackboardValue
* Created new C++ BTTaskNode class  BTTask_Shoot
* Created new C++ BTService_BlackboardBase class BTService_UpdatePlayerLocation and its derived C++ class BTService_PlayerLocationIfSeen

### Day 05
* Roughly completed AI system
* Created new widget blueprint class WBP_LoseScreen
* Created new widget blueprint class WBP_VictoryScreen
* Created new widget blueprit class WBP_StartScreen
* Created new level MainMenu
* Created new widget blueprint class WBP_MainMenu

### Day 06
* Created new widget blueprint class WBP_PasueMenu
* Created new sound cue SC_RifleShoot and SC_RifleImpactConcrete
* Created new sound attenuation SoundAttenuation_Default
* Created new widget blueprint class WBP_HUD
* Many bugs need to fix

### Day 07
* Implemented player health display
* Created new widget blueprint WBP_EnemyHealthBar and added it to BP_EnemyShooter
* Added jump animation
* Added background music
* Fixed some but there are still a lot  of bugs 
* End course section