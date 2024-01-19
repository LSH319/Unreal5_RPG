# Animation

# Weapon Equip

### 스켈레탈 메시에 소켓을 추가하여 무기가 부착 될 위치 조정

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled.png)

### 애님 몽타주와 노티파이를 활용하여 타이밍 체크

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%201.png)

### Weapon 부착을 위한 코드 추가

```cpp
void AMyCharacter::Disarm()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
	}
}

void AMyCharacter::Arm()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
	}
}
```

### 애니메이션 블루프린트에서 이벤트 그래프 활용

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%202.png)

### 결과물

![장착탈착.gif](Animation%2033b75fdd365c44f8b93b3544d35ba53e/%25EC%259E%25A5%25EC%25B0%25A9%25ED%2583%2588%25EC%25B0%25A9.gif)

# Cached Pose

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%203.png)

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%204.png)

애니메이션 포즈의 결과를 저장하여 다른곳에서 사용 가능

# Linked Anim Graph

ABP_Echo

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%205.png)

ABP_Echo_MainState

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%206.png)

애니메이션 블루프린트에서 다른 애니메이션 블루프린트를 불러와 사용하는 방식

# 애님 몽타주 노티파이 활용

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%207.png)

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%208.png)

사운드 재생, 공격 시작 및 종료시 노티파이를 추가

해당 노티파이 수신시 행동을 블루프린트에 추가하여 사용

# Motion Warping

사용을 위해선 플러그인 추가

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%209.png)

타겟을 설정하여 애님 몽타주 실행중 방향 전환 혹은 이동에 사용 가능

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%2010.png)

# IK 릭과 IK 리타게터를 활용한 애니메이션 활용

애니메이션을 다른 스켈레톤에서 사용하기 위한 과정

## IK 릭 생성

애니메이션을 보유한 스켈레톤과 애니메이션을 사용하고 싶은 스켈레톤에서 진행

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%2011.png)

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%2012.png)

1. 리타겟 루트 설정
2. 체인 추가 및 체인 이름 설정

## IK 리타게터 생성

![Untitled](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Untitled%2013.png)

IK 리타게터를 생성해 소스와 타깃을 설정

변경하고 싶은 애니메이션 선택후 익스포트 하여 사용

- 두 스켈레탈의 포즈가 다를경우 예상과 다른 움직임을 보이므로 포즈를 맞춰야함

## 리타게터 결과

![Anim.gif](Animation%2033b75fdd365c44f8b93b3544d35ba53e/Anim.gif)