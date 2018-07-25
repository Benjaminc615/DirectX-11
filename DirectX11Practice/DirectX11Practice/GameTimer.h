#pragma once


class GameTimer
{
public:
	GameTimer();

	float TotalTime() const;
	float DeltaTime() const;

	void Reset();
	void Start();
	void Stop();
	void Tick();

private:
	double mSecondPerCount;
	double mDeltaTime;

	__int64 mBaseTime;
	__int64 mCurrTime;
	__int64 mPauseTime;
	__int64 mStopTime;
	__int64 mPrevTime;

	bool mStopped;
};