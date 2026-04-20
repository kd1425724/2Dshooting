#pragma once
#include<functional>

using namespace std;

enum FeedState
{
	NoFeed,		//0
	FeedIn,		//1
	FeedOut		//2
};

class C_Feed
{
public:
	~C_Feed(){}

	//time...何フレームでフェード処理が終わるか
	void FeedInInit(float time);
	//time...何フレームでフェード処理が終わるか
	//finishpattern...フェード処理終わった後何をするか
	void FeedOutInit(float time,function<void()> finishpattern);

	void Update();
	void Draw();

	void FeedEnd();

	FeedState GetFeedState()const { return m_state; }

private:

	//フェード処理が終わったら何をするか
	function<void()> m_finishpattern;

	//フェードインかアウトか
	FeedState m_state;

	float m_alpha;

	//減らすスピード
	float m_delta;

	//フェード処理中か
	bool m_feedflg;

	Math::Matrix m_mat;

//シングルトン
private:
	C_Feed() {}

public:

	static C_Feed& GetInstans()
	{
		static C_Feed instans;
		return instans;
	}
};
//フェード処理
#define FEED C_Feed::GetInstans()
