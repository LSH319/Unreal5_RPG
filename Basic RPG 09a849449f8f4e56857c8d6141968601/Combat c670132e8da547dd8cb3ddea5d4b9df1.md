# Combat

# 공격 중에만 Overlap 이벤트 발생

애님 몽타주에서 노티파이 추가

![Untitled](Combat%20c670132e8da547dd8cb3ddea5d4b9df1/Untitled.png)

노티파이에 따라 무기의 Collision을 변경하여 공격중에만 overlap 이벤트가 발생하도록 적용

![Untitled](Combat%20c670132e8da547dd8cb3ddea5d4b9df1/Untitled%201.png)

# 공격모션 랜덤 재생

각 공격을 섹션으로 분리

![Untitled](Combat%20c670132e8da547dd8cb3ddea5d4b9df1/Untitled.png)

공격시 섹션 이름 설정

![Untitled](Combat%20c670132e8da547dd8cb3ddea5d4b9df1/Untitled%202.png)

설정되어 있는 애님 몽타주와 섹션 이름으로 랜덤한 공격 애니메이션 재생

```cpp

int32 ABaseCharacter::PlayAttackMontage()
{
	return PlayRandomMontageSection(AttackMontage, AttackMontageSections);
}

int32 ABaseCharacter::PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames)
{
	if (SectionNames.Num() <= 0) return -1;
	const int32 MaxSectionIndex = SectionNames.Num() - 1;
	const int32 Selection = FMath::RandRange(0, MaxSectionIndex);
	PlayMontageSection(Montage, SectionNames[Selection]);
	return Selection;
}
```

# 피격 방향에 따른 피격 애니메이션 및 효과

피격시 피격 포인트와 액터의 위치를 활용하여 방향 계산

결과값에 따른 피격 애니메이션 재생

## 애님 몽타주 추가 및 방향에 따른 섹션 분류

![Untitled](Combat%20c670132e8da547dd8cb3ddea5d4b9df1/Untitled%203.png)

각 애니메이션에 따른 섹션 설정 및 몽타주 연결 삭제

## 피격 방향 계산

```cpp
void ABaseCharacter::DirectionalHitReact(const FVector& ImpactPoint)
{
	const FVector Forward = GetActorForwardVector();
	const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	const FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();
	
	const double CosTheta = FVector::DotProduct(Forward, ToHit);
	double Theta = FMath::Acos(CosTheta);
	Theta = FMath::RadiansToDegrees(Theta);

	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);
	if (CrossProduct.Z < 0)
	{
		Theta *= -1.f;
	}
	FName Section("FromBack");

	if (Theta >= -45.f && Theta < 45.f)
	{
		Section = FName("FromFront");
	}
	else if (Theta >= -135.f && Theta < -45.f)
	{
		Section = FName("FromLeft");
	}
	else if (Theta >= 45.f && Theta < 135.f)
	{
		Section = FName("FromRight");
	}

	PlayHitReactMontage(Section);
}

void ABaseCharacter::PlayHitReactMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HitReactMontage)
	{
		AnimInstance->Montage_Play(HitReactMontage);
		AnimInstance->Montage_JumpToSection(SectionName, HitReactMontage);
	}
}
```

피격 방향 계산 후 그에 맞는 섹션 이름 전달

섹션 이름을 기반으로 애님몽타주 실행

## 피격 이펙트

```cpp
//.h
UPROPERTY(EditAnywhere)
UParticleSystem* HitParticles;

//.cpp
void ABaseCharacter::SpawnHitParticles(const FVector& ImpactPoint)
{
	if (HitParticles && GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticles,
			ImpactPoint
		);
	}
}
```

피격 위치를 받아 설정해둔 파티클 이펙트를 해당 위치에 스폰

![Untitled](Combat%20c670132e8da547dd8cb3ddea5d4b9df1/Untitled%204.png)

해당 액터에 파티클 이펙트 세팅

# 피격시 대미지 처리

언리얼엔진에서 제공해주는 `ApplyDamage`와 `TakeDamage` 활용

```cpp
float UGameplayStatics::ApplyDamage(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageTypeClass)

float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);
```

Weapon class에서 Overlap시 `ApplyDamage` 호출

```cpp
void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FHitResult BoxHit;
	BoxTrace(BoxHit);

	if (BoxHit.GetActor())
	{
		UGameplayStatics::ApplyDamage(BoxHit.GetActor(), Damage, GetInstigator()->GetController(), this, UDamageType::StaticClass());
	}
}
```

`ApplyDamage`호출시 전달한 actor의 `TakeDamage` 호출

`TakeDamage` 에서 Attribute 수정

```cpp
float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if (Attributes)
	{
		Attributes->ReceiveDamage(DamageAmount);
	}
	return DamageAmount;
}
```

## 피격시 애니메이션 결과

![Front.gif](Combat%20c670132e8da547dd8cb3ddea5d4b9df1/Front.gif)

![Back.gif](Combat%20c670132e8da547dd8cb3ddea5d4b9df1/Back.gif)

![Left.gif](Combat%20c670132e8da547dd8cb3ddea5d4b9df1/Left.gif)

![Right.gif](Combat%20c670132e8da547dd8cb3ddea5d4b9df1/Right.gif)