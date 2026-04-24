#pragma once
#include <vector>
#include "Game.h"

enum BONEINDEX : DWORD
{
	pelvis = 1,
	spine_1 = 3,
	spine_2 = 4,
	neck_0 = 6,
	head = 7,
	arm_upper_L = 9,
	arm_lower_L = 10,
	hand_L = 11,
	arm_upper_R = 13,
	arm_lower_R = 14,
	hand_R = 15,
	leg_upper_L = 17,
	leg_lower_L = 18,
	ankle_L = 19,
	leg_upper_R = 20,
	leg_lower_R = 21,
	ankle_R = 22,
};

struct BoneJointData
{
	Vec3 Pos;
	char pad[0x14];
};

struct BoneJointPos
{
	Vec3 Pos;
	Vec2 ScreenPos;
	bool IsVisible = false;
};

class CBone
{
private:
	DWORD64 EntityPawnAddress = 0;
public:
	DWORD64 BoneArrayAddress;
	std::vector<BoneJointPos> BonePosList;

	bool UpdateAllBoneData(const DWORD64& EntityPawnAddress);
};

namespace BoneJointList
{
	inline std::list<DWORD> Trunk = { neck_0,spine_2, pelvis };

	inline std::list<DWORD> LeftArm = { neck_0,  arm_upper_L, arm_lower_L, hand_L };

	inline std::list<DWORD> RightArm = { neck_0, arm_upper_R,arm_lower_R, hand_R };

	inline std::list<DWORD> LeftLeg = { pelvis, leg_upper_L , leg_lower_L, ankle_L };

	inline std::list<DWORD> RightLeg = { pelvis, leg_upper_R , leg_lower_R, ankle_R };

	inline std::vector<std::list<DWORD>> List = { Trunk, LeftArm, RightArm, LeftLeg, RightLeg };
}