#pragma once
#include<math.h>
//#include <WinBase.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include "lp_filter.h"

#define PI 3.141592653589793
#define PI_2 3.141592653589793 * 0.5
#define r2d 180/PI
#define d2r PI/180


#define JNT_NUM 6
#define ARM_NUM 2


typedef double REAL;


//class CARTESIAN
//{
//public:
//	REAL x;
//	REAL y;
//	REAL z;
//};
//
//class ROT_MATRIX
//{
//public:
//	REAL m[3][3];
//};
//
//class TRANS_MATRIX
//{
//public:
//	REAL t[4][4];
//};
//
//class QUATERNION
//{
//public:
//	REAL u0, u1, u2, u3;
//};
//
//class POSE
//{
//public:
//	CARTESIAN pos;
//	QUATERNION quat;
//};
//
//class POSE_EULER
//{
//public:
//	REAL pos[3];
//	REAL euler[3];
//};
//
//class ARM_JOINT
//{
//public:
//	REAL joint[JNT_NUM];
//	REAL m_cnt[JNT_NUM];
//};
//
//class BODY
//{
//public:
//	REAL rx;
//	REAL ry;
//	POSE chest_pose;
//	POSE L_arm_base;
//	POSE R_arm_base;
//	REAL chest_L3;
//	REAL waist_L2;
//	REAL foot_Ll;
//	LowPassFilter2p lpf_body[2];
//};
//
//class HEAD
//{
//public:
//	REAL ry;
//	REAL rz;
//	POSE head_pose;
//};
//
//class ARMS
//{
//public:
//	REAL DH[JNT_NUM][4];
//	ARM_JOINT arm_J_pos;
//	ARM_JOINT arm_J_pos_last;
//	ARM_JOINT arm_J_spd;
//	ARM_JOINT arm_J_spd_last;
//	ARM_JOINT arm_J_acc;
//	ARM_JOINT arm_J_spd_lim;
//	ARM_JOINT arm_J_acc_lim;
//	ARM_JOINT arm_J_pos_fdb;
//	ARM_JOINT arm_J_spd_ratio;
//	ARM_JOINT arm_J_acc_ratio;
//	ARM_JOINT targ_q;
//	ARM_JOINT init_q;
//	REAL L;
//	REAL dl;
//	REAL dq[JNT_NUM];
//	REAL norm_dq;
//	TRANS_MATRIX dT;
//	POSE base;
//	TRANS_MATRIX T_base;
//	LowPassFilter2p lpf_arms[JNT_NUM];
//	void calc_j2m(REAL gear, BOOL inv, BOOL is_se, REAL *j1, REAL *j2, REAL *m1, REAL *m2);
//	void calc_m2j(REAL gear, BOOL inv, BOOL is_se, REAL *m1, REAL *m2, REAL *j1, REAL *j2);
//};
//
//typedef enum
//{
//	POSE_CONTROL = 1,
//	JOINT_CONTROL = 2,
//	SLAVE_CONTROL = 3,
//	PRE_POS_CONTROL = 4,
//}CONTROL_MODE;
//
//class NUR_RBT
//{
//public:
//	CONTROL_MODE control_mode;
//	ARMS arms[ARM_NUM];
//	BODY body;
//	HEAD neck;
//private:
//
//};

typedef enum
{
	POSE_CONTROL = 1,
	JOINT_CONTROL = 2,
	SLAVE_CONTROL = 3,
	PRE_POS_CONTROL = 4,
}CONTROL_MODE;
class CARTESIAN
{
public:
	REAL x;
	REAL y;
	REAL z;
};

class ROT_MATRIX
{
public:
	REAL m[3][3];
};

class TRANS_MATRIX
{
public:
	REAL t[4][4];
};

class QUATERNION
{
public:
	REAL u0, u1, u2, u3;
};

class POSE
{
public:
	CARTESIAN pos;
	QUATERNION quat;
};

class POSE_EULER
{
public:
	REAL pos[3];
	REAL euler[3];
};
typedef struct
{

	double temp_step[JNT_NUM];
	double last_step[JNT_NUM];
	double ramp_joint[JNT_NUM];
	int ramp_len;
	int ramp_count[JNT_NUM];


}JOINT_;
typedef struct
{
	double temp_pose[JNT_NUM];
	double temp_euler[JNT_NUM];
	double last_pose[JNT_NUM];
	double last_euler[JNT_NUM];
	int ramp_len;
	int ramp_count;
	double ramp_pose[JNT_NUM];
	double ramp_euler[JNT_NUM];


}POSE_;

typedef struct
{
	double init_joint[6];
	double goal_joint[6];
	double norm;
	double temp_norm;
	double y;
	double x;
	double dq[6];
	double temp_dq[6];


}PREPOSE_;

typedef struct 
{
	REAL DH[JNT_NUM][4];
	JOINT_  joint;
	POSE_  pose[JNT_NUM];
	PREPOSE_  prepose[JNT_NUM];
	double fdb_value[JNT_NUM];
	double  out_value[JNT_NUM];
	POSE base;
	TRANS_MATRIX T_base;
	TRANS_MATRIX dT;
}ARM;


typedef struct
{

	double temp_step[2];
	double last_step[2];
	double ramp_joint[2];
	int ramp_len;
	int ramp_count[2];

}joint_wasit;

typedef struct
{
	double init_joint[2];
	double goal_joint[2];
	double norm;
	double temp_norm;
	double y;
	double x;
	double dq[2];
	double temp_dq[2];

}prepose_wasit;
typedef struct
{
	joint_wasit i_y_k;
	prepose_wasit p_y_k;
	double fdb_y_k[2];
	double out_y_k[2];


}waist;
class rbt_process
{


public:

	ARM left;
	ARM right;
	CONTROL_MODE control_mode;
	waist waist;
};

class Nur_Rbt
{
public:
	rbt_process nrbt_data;
	Nur_Rbt();
	~Nur_Rbt();

	void RbtRotX(REAL dTheta, ROT_MATRIX* dRotX);// 绕X旋转矩阵
	void RbtRotY(REAL dTheta, ROT_MATRIX* dRotY);//绕Y旋转矩阵
	void RbtRotZ(REAL dTheta, ROT_MATRIX* dRotZ);//绕Z旋转矩阵
	void zyxEuler2rotm(REAL euler_zyx[3], ROT_MATRIX rotm);//欧拉角转旋转矩阵
	void rotm2zyxEuler(ROT_MATRIX rotm, REAL dEulerZyx[3]);//旋转矩阵转欧拉角
	void rotm2Rpy(ROT_MATRIX rotm, REAL dRpy[3]);//旋转矩阵转RPY
	void RbtMulMtrx(int m, int n, int p, REAL* A, REAL* B, REAL* C);//多维矩阵乘法
	void RbtCross(REAL* u, REAL* v, REAL* n);//叉乘
	void fkine_Rbt_DH_jog(TRANS_MATRIX T_base, REAL Joint_sr[JNT_NUM], REAL DH[JNT_NUM][4],
		REAL steps_pos[3], REAL steps_orin[3], TRANS_MATRIX* dT0n);//求位姿调整后的末端矩阵
	void fkine_Rbt_DH(TRANS_MATRIX T_base, REAL Joint_sr[JNT_NUM], REAL DH[JNT_NUM][4], TRANS_MATRIX* dT0n);//求当前矩阵
	void calc_Tn(int num, REAL DH[JNT_NUM][4], TRANS_MATRIX* Tn);//计算某两个自由度之间的旋转矩阵
	int RbtInvMtrx(REAL* C, REAL* IC, int n);//求矩阵的逆
	void PInvMtrx66(REAL AA[6][JNT_NUM], REAL AA_pinv[JNT_NUM][6]);//求伪逆（右逆）
	void Transpose_Mtrx66(REAL AA[6][JNT_NUM], REAL AA_Transpose[JNT_NUM][6]);//求转置
	void CalJcb_DH(REAL DH[JNT_NUM][4], REAL Joint_sr[JNT_NUM], REAL dRbtJcb[6][JNT_NUM], TRANS_MATRIX* T0n_c);//求雅可比矩阵
	int ikine_IteraFcn2(TRANS_MATRIX T_base, REAL DH[JNT_NUM][4],
		TRANS_MATRIX* T0n_d, REAL JntCurrent[JNT_NUM], REAL JntCalcted[JNT_NUM]);////反求各角度移动距离
	REAL lspb_plan(REAL V, REAL dl);//V:(1,2)   dl:[0,1]//轨迹规划
	REAL norm_array(REAL* C, int n);//求平方和
	void get_rot_from_T(TRANS_MATRIX* Tn, ROT_MATRIX* rn);
	void set_rot_to_T(ROT_MATRIX* rn, TRANS_MATRIX* Tn);
	void quaternion_rot_matrix_to_quaternion(
		QUATERNION* qr,       /* Output quaternion */
		const ROT_MATRIX* m);//旋转转四元数
	void quaternion_to_rot_matrix(
		const QUATERNION* q,  /* Input quaternion */
		ROT_MATRIX* mr);//四元数转旋转
	void pose_to_T(POSE* pose, TRANS_MATRIX* T);
	REAL sin_ramp_creater(int ramp_len, int idx, REAL* cur, REAL* goal);//正弦过度
	void Euler2quaternion(REAL* C, QUATERNION* qr);
	void calc_j2m(REAL gear, BOOL inv, BOOL is_se, REAL * j1, REAL * j2, REAL * m1, REAL * m2);
	void calc_m2j(REAL gear, BOOL inv, BOOL is_se, REAL *m1, REAL *m2, REAL *j1, REAL *j2);
	//int ramp_len;
	//ARM_JOINT last_joint_steps[ARM_NUM];
	//ARM_JOINT joint_steps_ramp_ratio[ARM_NUM];
	//ARM_JOINT temp_joint_steps[ARM_NUM];
	//int joint_ramp_idx[ARM_NUM];

	//POSE_EULER last_pose_steps[ARM_NUM];
	//POSE_EULER pose_steps_ramp_ratio[ARM_NUM];
	//POSE_EULER temp_pose_steps[ARM_NUM];
	//int pose_ramp_idx[ARM_NUM];
private:

};