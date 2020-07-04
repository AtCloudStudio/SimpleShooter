// Copyright @CloudStudio 2020

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"
#include "PlayerShooter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SIMPLESHOOTER_API APlayerShooter : public AShooterCharacter
{
	GENERATED_BODY()

public:
	APlayerShooter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Components
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* ThirdPersonCamera;
	
	// Movement
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 100.0f;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.0f;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUp(float AxisValue);
	void LookRight(float AxisValue);

protected:
	virtual void BeginPlay() override;
	virtual void HandleDeath() override;
};