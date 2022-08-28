// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "MetaTypes.generated.h"

/**
 * 
 */



UCLASS()
class METACOMMON_API UMetaTypes : public UObject
{
	GENERATED_BODY()
	
};


#pragma region DebugHelper

class METACOMMON_API SSCRecord
{
private:
	static TSharedPtr<SSCRecord> RecordInst;
public:
	inline SSCRecord() {};
	~SSCRecord() {};

	static TSharedPtr<SSCRecord> Get();

public:
	void InitParam(float _showTime, FColor _showColor);
	void SetShowPattern(int32 _showPattern);
	inline void OutPut()
	{
		switch (showPattern)
		{
		case 0:
		{
			if (GEngine) {
				GEngine->AddOnScreenDebugMessage(-1, showTime, showColor, showInfo);
			}
		}
		break;
		case 1:
		{
			UE_LOG(LogTemp, Log, TEXT("%s"), *showInfo);
		}
		break;
		case 2:
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *showInfo);
		}
		break;
		case 3:
		{
			UE_LOG(LogTemp, Error, TEXT("%s"), *showInfo);
		}
		break;
		}
		showInfo.Empty();
	}

	inline SSCRecord& operator<<(FString Info) { showInfo.Append(Info); return *this; }
	inline SSCRecord& operator<<(FName Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FText Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(const char* Info) { showInfo += Info; return *this; }
	inline SSCRecord& operator<<(const char Info) { showInfo.AppendChar(Info); return *this; }
	inline SSCRecord& operator<<(int32 Info) { showInfo.Append(FString::FromInt(Info)); return *this; }
	inline SSCRecord& operator<<(float Info) { showInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline SSCRecord& operator<<(double Info) { showInfo.Append(FString::SanitizeFloat(Info)); return *this; }
	inline SSCRecord& operator<<(bool Info) { showInfo.Append(Info ? FString("true") : FString("false")); return *this; }
	inline SSCRecord& operator<<(FVector2D Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FVector Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FRotator Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FQuat Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FTransform Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FMatrix Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FColor Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FLinearColor Info) { showInfo.Append(Info.ToString()); return *this; }
	inline SSCRecord& operator<<(FMargin Info) { showInfo.Append((FString::SanitizeFloat(Info.Left) + FString(" , ") + FString::SanitizeFloat(Info.Top) + FString(" , ") + FString::SanitizeFloat(Info.Right) + FString(" , ") + FString::SanitizeFloat(Info.Bottom))); return *this; }

	inline SSCRecord& operator<<(SSCRecord& _RecordInst) { _RecordInst.OutPut(); return *this; }


private:
	FString showInfo;
	float showTime = 0.f;
	FColor showColor = FColor::Yellow;
	uint8 showPattern = 0;  // 0 Debug 1 Log 2 Warning 3 Error
};

#pragma endregion


namespace SSCHelper
{

	FORCEINLINE SSCRecord& Debug(float showTime, FColor showColor)
	{
		SSCRecord::Get()->SetShowPattern(0);
		SSCRecord::Get()->InitParam(showTime, showColor);
		return *SSCRecord::Get();
	}

	FORCEINLINE SSCRecord& Debug(FColor showColor)
	{
		return Debug(300.f, showColor);
	}

	FORCEINLINE SSCRecord& Debug()
	{
		return Debug(300.f, FColor::Yellow);
	}


	FORCEINLINE SSCRecord& Log(float showTime, FColor showColor)
	{
		SSCRecord::Get()->SetShowPattern(1);
		SSCRecord::Get()->InitParam(showTime, showColor);
		return *SSCRecord::Get();
	}

	FORCEINLINE SSCRecord& Warning(float showTime, FColor showColor)
	{
		SSCRecord::Get()->SetShowPattern(2);
		SSCRecord::Get()->InitParam(showTime, showColor);
		return *SSCRecord::Get();
	}

	FORCEINLINE SSCRecord& Error(float showTime, FColor showColor)
	{
		SSCRecord::Get()->SetShowPattern(3);
		SSCRecord::Get()->InitParam(showTime, showColor);
		return *SSCRecord::Get();
	}

	FORCEINLINE SSCRecord& Endl()
	{
		return *SSCRecord::Get();
	}


	

}





