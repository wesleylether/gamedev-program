

#include "SineWaveRotation.h"

void ASineWaveRotation::BeginPlay()
{
	Super::BeginPlay();

	InitialRotation = GetActorRotation();
}

void ASineWaveRotation::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	auto GetFrequency = [](const float Speed, const float MaxAngle) -> float {
		return MaxAngle != 0.0f ? (PI * Speed) / MaxAngle : 0.0f;
	};

	const float PitchFreq = GetFrequency(RotationSpeeds.Pitch, MaxAngles.Pitch);
	const float YawFreq = GetFrequency(RotationSpeeds.Yaw, MaxAngles.Yaw);
	const float RollFreq = GetFrequency(RotationSpeeds.Roll, MaxAngles.Roll);

	const float PitchOffset = FMath::Sin(RunningTime * PitchFreq) * MaxAngles.Pitch;
	const float YawOffset = FMath::Sin(RunningTime * YawFreq) * MaxAngles.Yaw;
	const float RollOffset = FMath::Sin(RunningTime * RollFreq) * MaxAngles.Roll;

	const FRotator NewRotation = InitialRotation + FRotator(PitchOffset, YawOffset, RollOffset);
	SetActorRotation(NewRotation);
}
