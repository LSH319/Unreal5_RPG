# Enhanced Input

Enhanced Input을 활용한 인풋 제어

# 사용전 확인 사항

## C++

### Build.cs 에서 `"EnhancedInput"`모듈 추가

## Unreal

### 플러그인 추가

![Untitled](Enhanced%20Input%20101906a3bc7d456faa64f3090e81734a/Untitled.png)

### 프로젝트 세팅의 입력 Default Classes 확인

![Untitled](Enhanced%20Input%20101906a3bc7d456faa64f3090e81734a/Untitled%201.png)

# C++

### `PlayerController`를 상속받는 Controller class 생성

### `InputMappingContext` , `InputAction` 및 `InputAction`에 바인딩될 함수 추가

```cpp
UPROPERTY(EditAnywhere)
TObjectPtr<UInputMappingContext> MyContext;

UPROPERTY(EditAnywhere)
TObjectPtr<UInputAction> MyAction;

void BindFunction(const FInputActionValue& InputActionValue);
```

### `BeginPlay` 에서 `InputMappingContext` 체크 및 등록

```cpp
void AMyController::BeginPlay()
{
	Super::BeginPlay();

	check(MyContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(MyContext, 0);
	}
}
```

### `SetupInputComponent` 에서 익풋 액션에 함수 바인딩

```cpp
void AMyController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MyAction, ETriggerEvent::Triggered, this, &AMyController::BindFunction);
}
```

### 바인딩 해줄 함수 생성

```cpp
void AMyController::BindFunction(const FInputActionValue& InputActionValue)
{

}
```

`InputActionValue`의 값은 인풋액션에서 설정한 타입으로 수신 가능

사용 예시(인풋 액션에서 값 타입을 `Vector2D`로 설정한 경우)

```cpp
void AMyController::BindFunction(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
  // InputAxisVector.X InputAxisVector.Y 로 접근 가능
}
```

# Unreal Engine

### 인풋 액션 생성

![Untitled](Enhanced%20Input%20101906a3bc7d456faa64f3090e81734a/Untitled%202.png)

필요에 따라 속성 변경

### 입력 매핑 컨텍스트 생성 및 인풋 액션 바인딩

![Untitled](Enhanced%20Input%20101906a3bc7d456faa64f3090e81734a/Untitled%203.png)

생성해둔 인풋 액션을 매핑

필요에 따라 속성 변경

### Controller 블루프린트 생성

![Untitled](Enhanced%20Input%20101906a3bc7d456faa64f3090e81734a/Untitled%204.png)

블루프린트 생성 시 C++에서 생성한 클래스를 기반으로 생성

클래스 내부에서 선언한 입력 매핑 컨텍스트와 인풋 액션 세팅

이후 GameMode에서 플레이어 컨트롤러 클래스 변경

## 애니메이션이 적용된 이동

![move.gif](Enhanced%20Input%20101906a3bc7d456faa64f3090e81734a/move.gif)