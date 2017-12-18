#ifndef UFI_ANIM_H
#define UFI_ANIM_H

class UFI_Anim
{
private:
	UFI_Anim(const UFI_Anim& rhs);
	UFI_Anim& operator=(const UFI_Anim& rhs);
	int timestep_p;
	int period_p;

	int N_state = 0;
	int N = 0;
	int from_p;
	int to_p;
	int param;
	
	bool NeedUpdate = true;
	
	std::vector<int>		Anim_IntVec;
	std::vector<SDL_Point>	Anim_PointVec;
	std::vector<SDL_Rect>	Anim_RectVec;

public:
	UFI_Anim();
	~UFI_Anim();
	void SetTime( int timestep, int period);
	void SetAnim( int from, int to );
	void Start();
	int Update();
	int GetN();
	
	void SetLinear(void);
	void SetSigmoid(void);
};

#endif // UFI_ANIM_H
