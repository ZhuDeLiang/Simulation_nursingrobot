#include "rbt_math.h"


REAL g_DH[JNT_NUM][4] = { {PI / 2,     PI / 2,         0.f,      0.f},
						{-PI / 2,      PI / 2,      116.72,    242.79},
						{PI * 2 / 3,   PI / 2,         0.f,      0.f},
						{0.f,		  -PI / 2,         0.f,    330.f},
						{0.f,		   PI / 2,         0.f,      0.f},
						{0.f,          0.f,            0.f,    233.f} };
REAL base_frame_l[7] = { 0.f, 126.246505495981, -33.8276491948995, 0.701057384649978, -0.0922959556412573,0.0922959556412573, 0.701057384649978 };
REAL base_frame_r[7] = { 0.f,-126.246505495981, -33.8276491948995, 0.701057384649978,  0.0922959556412573,0.0922959556412573,-0.701057384649978 };





Nur_Rbt::Nur_Rbt()
{

	memset(&this->nrbt_data, 0, sizeof(this->nrbt_data));
	memcpy(&this->nrbt_data.left.DH, &g_DH, sizeof(g_DH));
	memcpy(&this->nrbt_data.right.DH, &g_DH, sizeof(g_DH));
	for (int i = 0; i < JNT_NUM; i++)
	{
		nrbt_data.left.joint.last_step[i] = 0;
		nrbt_data.left.joint.ramp_len = 20;
		nrbt_data.left.joint.ramp_joint[i] = 0;
		nrbt_data.left.joint.ramp_count[i] = 0;
	/*	nrbt_data.left.fdb_value[i] = 0;
		nrbt_data.left.out_value[i] = 0;*/

		nrbt_data.right.joint.last_step[i] = 0;
		nrbt_data.right.joint.ramp_len = 20;
		nrbt_data.right.joint.ramp_joint[i] = 0;
		nrbt_data.right.joint.ramp_count[i] = 0;
		nrbt_data.right.fdb_value[i] = 0;
		nrbt_data.right.out_value[i] = 0;
		nrbt_data.left.prepose->x = 1;
		nrbt_data.right.prepose->x = 1;
		
	}
	for (int i = 0; i < 2; i++)
	{

		nrbt_data.waist.i_y_k.ramp_len = 30;
		nrbt_data.waist.i_y_k.last_step[i] = 0;
		nrbt_data.waist.i_y_k.ramp_joint[i] = 0;
		nrbt_data.waist.i_y_k.ramp_count[i] = 0;
		nrbt_data.waist.p_y_k.x = 1;
		/*nrbt_data.waist.fdb_y_k[i] = 0;
		nrbt_data.waist.out_y_k[i] = 0;*/
	}
	memcpy(&this->nrbt_data.left.base, &base_frame_l, sizeof(base_frame_l));
	memcpy(&this->nrbt_data.right.base, &base_frame_r, sizeof(base_frame_r));
	this->pose_to_T(&this->nrbt_data.left.base, &this->nrbt_data.left.T_base);
	this->pose_to_T(&this->nrbt_data.right.base, &this->nrbt_data.right.T_base);

	for (int i = 0; i < 3; i++)
	{


		this->nrbt_data.left.pose->temp_euler[i] = 0.0f;
		this->nrbt_data.left.pose->temp_pose[i] = 0.f;
		this->nrbt_data.left.pose->ramp_len = 20;
		this->nrbt_data.left.pose->ramp_pose[i] = 0.0f;
		this->nrbt_data.left.pose->ramp_euler[i] = 0.0f;
		this->nrbt_data.left.pose->ramp_count = 0;
		this->nrbt_data.left.pose->last_euler[i] = 0.0f;
		this->nrbt_data.left.pose->last_pose[i] = 0.0f;




		this->nrbt_data.right.pose->temp_euler[i] = 0.0f;
		this->nrbt_data.right.pose->temp_pose[i] = 0.f;
		this->nrbt_data.right.pose->ramp_len = 20;
		this->nrbt_data.right.pose->ramp_pose[i] = 0.0f;
		this->nrbt_data.right.pose->ramp_euler[i] = 0.0f;
		this->nrbt_data.right.pose->ramp_count = 0;
		this->nrbt_data.right.pose->last_euler[i] = 0.0f;
		this->nrbt_data.right.pose->last_pose[i] = 0.0f;
	}
	/*int ai,i,j;

	memset(&this->nrbt, 0, sizeof(this->nrbt));

	for (ai = 0; ai < 2; ai++)
	{
		memcpy(this->nrbt.arms[ai].DH, &g_DH, sizeof(g_DH));
	}

	memcpy(&this->nrbt.arms[0].base, &base_frame_l, sizeof(base_frame_l));
	memcpy(&this->nrbt.arms[1].base, &base_frame_r, sizeof(base_frame_r));

	for (ai = 0; ai < ARM_NUM; ai++)
	{
		for (i = 0; i < JNT_NUM; i++)
		{
			this->nrbt.arms[ai].arm_J_acc_lim.joint[i] = (REAL)1e-4;
			this->nrbt.arms[ai].arm_J_spd_lim.joint[i] = (REAL)1e-4;
			this->nrbt.arms[ai].dq[i] = 0.f;
			this->last_joint_steps[ai].joint[i] = 0.0f;
			this->joint_steps_ramp_ratio[ai].joint[i] = 0.0f;
			this->temp_joint_steps[ai].joint[i] = 0.0f;
			
		}
		for (i = 0; i < 3; i++)
		{
			this->last_pose_steps[ai].pos[i] = 0.0f;
			this->last_pose_steps[ai].euler[i] = 0.0f;
			this->pose_steps_ramp_ratio[ai].pos[i] = 0.0f;
			this->pose_steps_ramp_ratio[ai].euler[i] = 0.0f;
			this->temp_pose_steps[ai].pos[i] = 0.0f;
			this->temp_pose_steps[ai].euler[i] = 0.0f;
		}
		this->ramp_len = 5;
		this->joint_ramp_idx[ai] = 5;
		this->pose_ramp_idx[ai] = 5;
		this->pose_to_T(&this->nrbt.arms[ai].base, &this->nrbt.arms[ai].T_base);*/
	/*}*/
}

Nur_Rbt::~Nur_Rbt()
{

}

void Nur_Rbt::RbtRotX(REAL dTheta, ROT_MATRIX* dRotX)
{
	dRotX->m[0][0] = 1.0;
	dRotX->m[0][1] = 0.0;
	dRotX->m[0][2] = 0.0;

	dRotX->m[1][0] = 0.0;
	dRotX->m[1][1] = cosf(dTheta);
	dRotX->m[1][2] = -sinf(dTheta);

	dRotX->m[2][0] = 0.0;
	dRotX->m[2][1] = sinf(dTheta);
	dRotX->m[2][2] = cosf(dTheta);
}

void Nur_Rbt::RbtRotY(REAL dTheta, ROT_MATRIX* dRotY)
{
	dRotY->m[0][0] = cosf(dTheta);
	dRotY->m[0][1] = 0.0;
	dRotY->m[0][2] = sinf(dTheta);

	dRotY->m[1][0] = 0.0;
	dRotY->m[1][1] = 1.0;
	dRotY->m[1][2] = 0.0;

	dRotY->m[2][0] = -sinf(dTheta);
	dRotY->m[2][1] = 0.0;
	dRotY->m[2][2] = cosf(dTheta);
}

void Nur_Rbt::RbtRotZ(REAL dTheta, ROT_MATRIX* dRotZ)
{
	dRotZ->m[0][0] = cosf(dTheta);
	dRotZ->m[0][1] = -sinf(dTheta);
	dRotZ->m[0][2] = 0.0;

	dRotZ->m[1][0] = sinf(dTheta);
	dRotZ->m[1][1] = cosf(dTheta);
	dRotZ->m[1][2] = 0.0;

	dRotZ->m[2][0] = 0.0;
	dRotZ->m[2][1] = 0.0;
	dRotZ->m[2][2] = 1.0;
}

void Nur_Rbt::zyxEuler2rotm(REAL euler_zyx[3], ROT_MATRIX rotm)
{
	REAL angle_z, angle_y, angle_x;

	angle_z = euler_zyx[0];
	angle_y = euler_zyx[1];
	angle_x = euler_zyx[2];

	rotm.m[0][0] = cosf(angle_z) * cosf(angle_y);
	rotm.m[0][1] = cosf(angle_z) * sinf(angle_y) * sinf(angle_x) - sinf(angle_z) * cosf(angle_x);
	rotm.m[0][2] = cosf(angle_z) * sinf(angle_y) * cosf(angle_x) + sinf(angle_z) * sinf(angle_x);

	rotm.m[1][0] = sinf(angle_z) * cosf(angle_y);
	rotm.m[1][1] = sinf(angle_z) * sinf(angle_y) * sinf(angle_x) + cosf(angle_z) * cosf(angle_x);
	rotm.m[1][2] = sinf(angle_z) * sinf(angle_y) * cosf(angle_x) - cosf(angle_z) * sinf(angle_x);

	rotm.m[2][0] = -sinf(angle_y);
	rotm.m[2][1] = cosf(angle_y) * sinf(angle_x);
	rotm.m[2][2] = cosf(angle_y) * cosf(angle_x);
}

void Nur_Rbt::rotm2zyxEuler(ROT_MATRIX rotm, REAL dEulerZyx[3])
{
	if ((fabs(rotm.m[2][1]) < 1e-12)
		&& (fabs(rotm.m[2][2]) < 1e-12))
	{
		dEulerZyx[2] = 0.0;//x
		dEulerZyx[1] = atan2f(-rotm.m[2][0], rotm.m[2][2]);//y
		dEulerZyx[0] = atan2f(-rotm.m[0][1], rotm.m[1][1]);//z	
	}
	else
	{
		dEulerZyx[2] = atan2f(rotm.m[2][1], rotm.m[2][2]);
		dEulerZyx[1] = atan2f(-rotm.m[2][0], (cosf(dEulerZyx[2]) * rotm.m[2][2] + sinf(dEulerZyx[2]) * rotm.m[2][1]));
		dEulerZyx[0] = atan2f(rotm.m[1][0], rotm.m[0][0]);
	}
}

void Nur_Rbt::rotm2Rpy(ROT_MATRIX rotm, REAL dRpy[3])
{
	if ((fabs(rotm.m[0][0]) < 1e-12)
		&& (fabs(rotm.m[1][0]) < 1e-12))
	{
		dRpy[2] = 0.0;
		dRpy[1] = atan2f(-rotm.m[2][0], rotm.m[0][0]);
		dRpy[0] = atan2f(-rotm.m[1][2], rotm.m[1][1]);
	}
	else
	{
		dRpy[2] = atan2f(rotm.m[1][0], rotm.m[0][0]);
		dRpy[1] = atan2f(-rotm.m[2][0], (cosf(dRpy[2]) * rotm.m[0][0] + sinf(dRpy[2]) * rotm.m[1][0]));
		dRpy[0] = atan2f(sinf(dRpy[2]) * rotm.m[0][2] - cosf(dRpy[2]) * rotm.m[1][2], cosf(dRpy[2]) * rotm.m[1][1] - sinf(dRpy[2]) * rotm.m[0][1]);
	}
}

void Nur_Rbt::RbtMulMtrx(int m, int n, int p, REAL* A, REAL* B, REAL* C)
{
	int i, j, k;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			C[n * i + j] = 0.0;
			for (k = 0; k < p; k++)
			{
				C[n * i + j] = C[n * i + j] + A[p * i + k] * B[n * k + j];
			}
		}
	}
}

void Nur_Rbt::RbtCross(REAL* u, REAL* v, REAL* n)
{
	n[0] = u[1] * v[2] - u[2] * v[1];
	n[1] = u[2] * v[0] - u[0] * v[2];
	n[2] = u[0] * v[1] - u[1] * v[0];
}

void Nur_Rbt::fkine_Rbt_DH_jog(TRANS_MATRIX T_base, REAL Joint_sr[JNT_NUM], REAL DH[JNT_NUM][4],
	REAL steps_pos[3], REAL steps_orin[3], TRANS_MATRIX* dT0n)
{
	REAL alpha_sr[JNT_NUM], a_sr[JNT_NUM], d_sr[JNT_NUM], qq[JNT_NUM], q0_sr[JNT_NUM];
	TRANS_MATRIX T1, T2;
	ROT_MATRIX rx, ry, rz;
	int i, j, k;

	for (i = 0; i < JNT_NUM; i++)
	{
		q0_sr[i] = DH[i][0];
		alpha_sr[i] = DH[i][1];
		a_sr[i] = DH[i][2];
		d_sr[i] = DH[i][3];
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (i == j)
			{
				dT0n->t[i][j] = 1.f;
			}
			else
			{
				dT0n->t[i][j] = 0.f;
			}
		}
	}

	for (i = 0; i < JNT_NUM; i++)
	{
		qq[i] = q0_sr[i] + Joint_sr[i];

		T1.t[0][0] = cosf(qq[i]);                      T1.t[0][1] = -cosf(alpha_sr[i]) * sinf(qq[i]);
		T1.t[0][2] = sinf(alpha_sr[i]) * sinf(qq[i]);     T1.t[0][3] = a_sr[i] * cosf(qq[i]);

		T1.t[1][0] = sinf(qq[i]);                      T1.t[1][1] = cosf(alpha_sr[i]) * cosf(qq[i]);
		T1.t[1][2] = -sinf(alpha_sr[i]) * cosf(qq[i]);    T1.t[1][3] = a_sr[i] * sinf(qq[i]);

		T1.t[2][0] = 0;  T1.t[2][1] = sinf(alpha_sr[i]); T1.t[2][2] = cosf(alpha_sr[i]);   T1.t[2][3] = d_sr[i];

		T1.t[3][0] = 0;  T1.t[3][1] = 0; T1.t[3][2] = 0;   T1.t[3][3] = 1;

		RbtMulMtrx(4, 4, 4, dT0n->t[0], T1.t[0], T2.t[0]);

		for (j = 0; j < 4; j++)
		{
			for (k = 0; k < 4; k++)
			{
				dT0n->t[j][k] = T2.t[j][k];
			}
		}

	}
	RbtMulMtrx(4, 4, 4, T_base.t[0], T2.t[0], dT0n->t[0]);

	{
		ROT_MATRIX temp_rot_zy, temp_rot_zyx, temp_rot_0n1, temp_rot_0n2;
		RbtRotZ(steps_orin[2], &rz);
		RbtRotY(steps_orin[1], &ry);
		RbtMulMtrx(3, 3, 3, rz.m[0], ry.m[0], temp_rot_zy.m[0]);
		RbtRotX(steps_orin[0], &rx);
		RbtMulMtrx(3, 3, 3, temp_rot_zy.m[0], rx.m[0], temp_rot_zyx.m[0]);
		get_rot_from_T(dT0n, &temp_rot_0n1);
		RbtMulMtrx(3, 3, 3, temp_rot_zyx.m[0], temp_rot_0n1.m[0], temp_rot_0n2.m[0]);
		set_rot_to_T(&temp_rot_0n2, dT0n);
		for (i = 0; i < 3; i++)
		{
			dT0n->t[i][3] += steps_pos[i];
		}
	}
}

void Nur_Rbt::fkine_Rbt_DH(TRANS_MATRIX T_base, REAL Joint_sr[JNT_NUM], REAL DH[JNT_NUM][4], TRANS_MATRIX* dT0n)
{
	REAL alpha_sr[JNT_NUM], a_sr[JNT_NUM], d_sr[JNT_NUM], qq[JNT_NUM], q0_sr[JNT_NUM];
	TRANS_MATRIX T1, T2;
	int i, j, k;

	for (i = 0; i < JNT_NUM; i++)
	{
		q0_sr[i] = DH[i][0];
		alpha_sr[i] = DH[i][1];
		a_sr[i] = DH[i][2];
		d_sr[i] = DH[i][3];
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (i == j)
			{
				dT0n->t[i][j] = 1.f;
			}
			else
			{
				dT0n->t[i][j] = 0.f;
			}
		}
	}

	for (i = 0; i < JNT_NUM; i++)
	{
		qq[i] = q0_sr[i] + Joint_sr[i];

		T1.t[0][0] = cosf(qq[i]);                      T1.t[0][1] = -cosf(alpha_sr[i]) * sinf(qq[i]);
		T1.t[0][2] = sinf(alpha_sr[i]) * sinf(qq[i]);     T1.t[0][3] = a_sr[i] * cosf(qq[i]);

		T1.t[1][0] = sinf(qq[i]);                      T1.t[1][1] = cosf(alpha_sr[i]) * cosf(qq[i]);
		T1.t[1][2] = -sinf(alpha_sr[i]) * cosf(qq[i]);    T1.t[1][3] = a_sr[i] * sinf(qq[i]);

		T1.t[2][0] = 0;  T1.t[2][1] = sinf(alpha_sr[i]); T1.t[2][2] = cosf(alpha_sr[i]);   T1.t[2][3] = d_sr[i];

		T1.t[3][0] = 0;  T1.t[3][1] = 0; T1.t[3][2] = 0;   T1.t[3][3] = 1;

		RbtMulMtrx(4, 4, 4, dT0n->t[0], T1.t[0], T2.t[0]);

		for (j = 0; j < 4; j++)
		{
			for (k = 0; k < 4; k++)
			{
				dT0n->t[j][k] = T2.t[j][k];
			}
		}
	}
	RbtMulMtrx(4, 4, 4, T_base.t[0], T2.t[0], dT0n->t[0]);

}

void Nur_Rbt::get_rot_from_T(TRANS_MATRIX* Tn, ROT_MATRIX* rn)
{
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			rn->m[i][j] = Tn->t[i][j];
		}
	}
}

void Nur_Rbt::set_rot_to_T(ROT_MATRIX* rn, TRANS_MATRIX* Tn)
{
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			Tn->t[i][j] = rn->m[i][j];
		}
	}
}

void Nur_Rbt::calc_Tn(int num, REAL DH[JNT_NUM][4], TRANS_MATRIX* Tn)
{
	REAL q = DH[num][0];
	REAL alpha = DH[num][1];
	REAL a = DH[num][2];
	REAL d = DH[num][3];

	Tn->t[0][0] = cosf(q);
	Tn->t[0][1] = -cosf(alpha) * sinf(q);
	Tn->t[0][2] = sinf(alpha) * sinf(q);
	Tn->t[0][3] = a * cosf(q);

	Tn->t[1][0] = sinf(q);
	Tn->t[1][1] = cosf(alpha) * cosf(q);
	Tn->t[1][2] = -sinf(alpha) * cosf(q);
	Tn->t[1][3] = a * sinf(q);

	Tn->t[2][0] = 0;
	Tn->t[2][1] = sinf(alpha);
	Tn->t[2][2] = cosf(alpha);
	Tn->t[2][3] = d;

	Tn->t[3][0] = 0;
	Tn->t[3][1] = 0;
	Tn->t[3][2] = 0;
	Tn->t[3][3] = 1;

}

int Nur_Rbt::RbtInvMtrx(REAL* C, REAL* IC, int n)
{
	int i, j, k, l;

	/* 单位阵*/
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			*(IC + i * n + j) = 0.0;
		}
		*(IC + i * n + i) = 1.0;
	}

	/* 化上三角阵*/
	for (j = 0; j < n; j++)
	{
		if (fabs(*(C + j * n + j)) > 1e-15) /* C[j][j]不等于0*/
		{
			/* IC阵的第j行除以C[j][j]*/
			for (k = 0; k < n; k++)
			{
				*(IC + j * n + k) /= *(C + j * n + j);
			}
			/* C阵的第j行除以C[j][j]*/
			for (k = n - 1; k >= j; k--)
			{
				*(C + j * n + k) /= *(C + j * n + j);
			}

			for (i = j + 1; i < n; i++)
			{
				/* IC阵的第i行 - C[i][j]*IC阵的第j行*/
				for (k = 0; k < n; k++)
				{
					*(IC + i * n + k) -= *(C + i * n + j) * *(IC + j * n + k);
				}
				/* C阵的第i行 - C[i][j]*C阵的第j行*/
				for (k = n - 1; k >= j; k--)
				{
					*(C + i * n + k) -= *(C + i * n + j) * *(C + j * n + k);
				}
			}
		}
		else if (j < n - 1)
		{

			for (l = j + 1; l < n; l++)
			{
				/* 若C阵第j行后的C[l][j]不等于0，第j行加上第l行*/
				if (fabs(*(C + l * n + j)) > 1e-15)
				{
					for (k = 0; k < n; k++)
					{
						*(IC + j * n + k) += *(IC + l * n + k);
					}
					for (k = n - 1; k >= j; k--)
					{
						*(C + j * n + k) += *(C + l * n + k);
					}
					/* IC阵的第j行除以C[j][j]*/
					for (k = 0; k < n; k++)
					{
						*(IC + j * n + k) /= *(C + j * n + j);
					}
					/* C阵的第j行除以C[j][j]*/
					for (k = n - 1; k >= j; k--)
					{
						*(C + j * n + k) /= *(C + j * n + j);
					}
					/* 第i行 - C[i][j]*第j行*/
					for (i = j + 1; i < n; i++)
					{
						for (k = 0; k < n; k++)
						{
							*(IC + i * n + k) -= *(C + i * n + j) * *(IC + j * n + k);
						}
						for (k = n - 1; k >= j; k--)
						{
							*(C + i * n + k) -= *(C + i * n + j) * *(C + j * n + k);
						}
					}
					break;
				}
			}

			if (l == n)  /* C[l][j] 全等于0*/
			{
				return (-1);   /*  矩阵的行列式为零，不可求逆*/
			}
		}
		else  /* C[n][n]等于0*/
		{
			return (-1);    /*  矩阵的行列式为零，不可求逆*/
		}
	}
	/* 化成单位阵*/
	for (j = n - 1; j >= 1; j--)
	{
		for (i = j - 1; i >= 0; i--)
		{
			for (k = 0; k < n; k++)
			{
				*(IC + i * n + k) -= *(C + i * n + j) * *(IC + j * n + k);
			}
			*(C + i * n + j) = 0;
		}
	}

	return (1);
}

void Nur_Rbt::PInvMtrx66(REAL AA[6][JNT_NUM], REAL AA_pinv[JNT_NUM][6])
{
	int i, j;
	REAL AA_T[6][6], BB[6][6], BB_Inv[6][6];

	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			AA_T[i][j] = AA[j][i];
		}
	}

	RbtMulMtrx(6, 6, 6, AA[0], AA_T[0], BB[0]); /*---BB = AA*AA_T----*/

	RbtInvMtrx(BB[0], BB_Inv[0], 6);

	RbtMulMtrx(6, 6, 6, AA_T[0], BB_Inv[0], AA_pinv[0]); /*---BB = AA*AA_T----*/
}

void Nur_Rbt::Transpose_Mtrx66(REAL AA[6][JNT_NUM], REAL AA_Transpose[JNT_NUM][6])
{
	int i, j;
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < JNT_NUM; j++)
		{
			AA_Transpose[j][i] = AA[i][j];
		}
	}
}

void Nur_Rbt::CalJcb_DH(REAL DH[JNT_NUM][4], REAL Joint_sr[JNT_NUM], REAL dRbtJcb[6][JNT_NUM], TRANS_MATRIX* T0n_c)
{
	TRANS_MATRIX T1, T2, Tn;
	REAL alpha_sr[JNT_NUM], a_sr[JNT_NUM], d_sr[JNT_NUM], qq[JNT_NUM], q0_sr[JNT_NUM];
	REAL zi_1[3], zi_1_All[3][JNT_NUM], P_i_1_n[3], P_i_All[3][JNT_NUM], Cros_Z_P[3];
	/*	REAL dRbtJcbE_Tran[3][6],dRbtJcbE_Rot[3][6];*/
	int i, j, k;
	for (i = 0; i < JNT_NUM; i++)
	{
		q0_sr[i] = DH[i][0];
		alpha_sr[i] = DH[i][1];
		a_sr[i] = DH[i][2];
		d_sr[i] = DH[i][3];
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (i == j)
			{
				Tn.t[i][j] = 1.f;
			}
			else
			{
				Tn.t[i][j] = 0.f;
			}
		}
	}

	for (i = 0; i < JNT_NUM; i++)
	{
		for (j = 0; j < 3; j++)
		{
			zi_1_All[j][i] = Tn.t[j][2];
		}

		qq[i] = q0_sr[i] + Joint_sr[i];
		T1.t[0][0] = cosf(qq[i]);                       T1.t[0][1] = -cosf(alpha_sr[i]) * sinf(qq[i]);
		T1.t[0][2] = sinf(alpha_sr[i]) * sinf(qq[i]);      T1.t[0][3] = a_sr[i] * cosf(qq[i]);

		T1.t[1][0] = sinf(qq[i]);                       T1.t[1][1] = cosf(alpha_sr[i]) * cosf(qq[i]);
		T1.t[1][2] = -sinf(alpha_sr[i]) * cosf(qq[i]);     T1.t[1][3] = a_sr[i] * sinf(qq[i]);

		T1.t[2][0] = 0;  T1.t[2][1] = sinf(alpha_sr[i]);  T1.t[2][2] = cosf(alpha_sr[i]);   T1.t[2][3] = d_sr[i];

		T1.t[3][0] = 0;  T1.t[3][1] = 0; T1.t[3][2] = 0;   T1.t[3][3] = 1;
		RbtMulMtrx(4, 4, 4, Tn.t[0], T1.t[0], T2.t[0]);

		for (j = 0; j < 4; j++)
		{
			for (k = 0; k < 4; k++)
			{
				Tn.t[j][k] = T2.t[j][k];
				/*	Trans_Matrix[j][4*i+k] = T6[j][k];*/
			}
		}

		for (j = 0; j < 3; j++)
		{
			P_i_All[j][i] = Tn.t[j][3];
		}
	}


	for (j = 0; j < 3; j++)
	{
		P_i_1_n[j] = P_i_All[j][JNT_NUM - 1];  /*P_0_n*/
	}


	for (i = 0; i < JNT_NUM; i++)
	{
		for (j = 0; j < 3; j++)
		{
			zi_1[j] = zi_1_All[j][i];
		}

		RbtCross(zi_1, P_i_1_n, Cros_Z_P);

		for (j = 0; j < 3; j++)
		{
			dRbtJcb[j][i] = Cros_Z_P[j];
			dRbtJcb[j + 3][i] = zi_1[j];
			P_i_1_n[j] = P_i_All[j][JNT_NUM - 1] - P_i_All[j][i];  /*P_0_n*/
		}
	}

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			T0n_c->t[i][j] = Tn.t[i][j];   /*---返回当前的末端位姿矩阵--*/
		}
	}
}

int Nur_Rbt::ikine_IteraFcn2(TRANS_MATRIX T_base, REAL DH[JNT_NUM][4], TRANS_MATRIX* Tbn_d,
	REAL JntCurrent[JNT_NUM], REAL JntCalcted[JNT_NUM])
{
	REAL DH_q0[JNT_NUM], DH_alpha[JNT_NUM], DH_a[JNT_NUM], DH_d[JNT_NUM];
	TRANS_MATRIX T0n_c = { 0 };
	TRANS_MATRIX inv_T_base = { 0 };
	TRANS_MATRIX T0n_d = { 0 };
	REAL dA[6], AttErrVec[3];
	REAL Jcb_0[6][JNT_NUM], Jcb_0_pinv[JNT_NUM][6];
	REAL q_Itera[JNT_NUM], dq[JNT_NUM], dq_norm;  /*---用于迭代的中间变量---*/
	REAL deltaQ;
	REAL efs;
	int solutionFlag;
	REAL n[3], o[3], a[3], nd[3], od[3], ad[3];
	REAL Cros1[3], Cros2[3], Cros3[3];

	int i, lmax, l_limit;

	lmax = 0;
	l_limit = 1000;
	deltaQ = 1;
	efs = 1e-8;
	solutionFlag = 0;

	for (i = 0; i < JNT_NUM; i++)
	{
		DH_q0[i] = DH[i][0];
		DH_alpha[i] = DH[i][1];
		DH_a[i] = DH[i][2];
		DH_d[i] = DH[i][3];

		q_Itera[i] = JntCurrent[i];
	}

	{
		RbtInvMtrx(T_base.t[0], inv_T_base.t[0], 4);
		RbtMulMtrx(4, 4, 4, inv_T_base.t[0], Tbn_d->t[0], T0n_d.t[0]);
	}

	while (lmax <= l_limit)
	{
		if (deltaQ > efs)
		{
			solutionFlag = 0;

			CalJcb_DH(DH, q_Itera, Jcb_0, &T0n_c);

			for (i = 0; i < 3; i++)
			{
				n[i] = T0n_c.t[i][0];
				o[i] = T0n_c.t[i][1];
				a[i] = T0n_c.t[i][2];

				nd[i] = T0n_d.t[i][0];
				od[i] = T0n_d.t[i][1];
				ad[i] = T0n_d.t[i][2];
			}

			RbtCross(n, nd, Cros1);
			RbtCross(o, od, Cros2);
			RbtCross(a, ad, Cros3);

			for (i = 0; i < 3; i++)
			{
				AttErrVec[i] = 0.5 * (Cros1[i] + Cros2[i] + Cros3[i]);  //---姿态误差

				dA[i] = T0n_d.t[i][3] - T0n_c.t[i][3];
				dA[i + 3] = AttErrVec[i];
			}

			PInvMtrx66(Jcb_0, Jcb_0_pinv);

			RbtMulMtrx(JNT_NUM, 1, 6, Jcb_0_pinv[0], dA, dq);

			dq_norm = 0;
			for (i = 0; i < JNT_NUM; i++)
			{
				dq_norm = dq_norm + dq[i] * dq[i];
			}
			deltaQ = dq_norm;


			for (i = 0; i < JNT_NUM; i++)
			{
				q_Itera[i] = q_Itera[i] + dq[i];
			}
		}
		else
		{
			solutionFlag = 1;   /*---求解成功---*/
		}
		lmax = lmax + 1;  /*---更新迭代次数---*/
	}

	if (solutionFlag == 1)
	{
		/************************************************************************/
		/*  范围[-pi, pi]---                                                    */
		/************************************************************************/
		for (i = 0; i < JNT_NUM; i++)
		{
			//q_Itera[i] = q_Itera[i]-DH_q0[i];
			while (q_Itera[i] > 2 * PI)  q_Itera[i] = q_Itera[i] - 2 * PI;
			while (q_Itera[i] < -2 * PI) q_Itera[i] = q_Itera[i] + 2 * PI;
		}

		for (i = 0; i < JNT_NUM; i++)
		{
			JntCalcted[i] = q_Itera[i];
		}
	}
	else
	{
		for (i = 0; i < JNT_NUM; i++)
		{
			JntCalcted[i] = JntCurrent[i];
		}
	}
	return solutionFlag;
}

REAL Nur_Rbt::lspb_plan(REAL V, REAL dl)//V:(1,2)   dl:[0,1]
{
	REAL L = -1.0f;
	REAL tb = 1.0f;
	REAL a = 0.0f;

	if (V >= 2.0f || V <= 1.0f)
	{
		V = 1.5f;
	}

	if (dl <= 1.0f && dl >= 0.0f)
	{
		tb = (-1 + V) / V;
		a = V / tb;

		if (dl <= tb)
		{
			//initial blend
			L = a * 0.5f * dl * dl;
		}
		else if (dl <= (1 - tb))
		{
			//linear motion
			L = (1 - V) * 0.5f + V * dl;
		}
		else
		{
			//final blend
			L = 1 - a / 2 + a * dl - 0.5f * a * dl * dl;
		}
	}

	return L;

}

REAL Nur_Rbt::norm_array(REAL* C, int n)
{
	REAL sum = 0.f;
	int i = 0;
	for (i = 0; i < n; i++)
	{
		sum += C[i] * C[i];
	}
	return sqrtf(sum);
}

void Nur_Rbt::quaternion_rot_matrix_to_quaternion(
	QUATERNION* qr,       /* Output quaternion */
	const ROT_MATRIX* m)  /* Input rotation matrix */
{
	const double trace = m->m[0][0] + m->m[1][1] + m->m[2][2];
	double root;
	double u0, u1, u2, u3;

	/*
	** maximize the denominator for numerical robustness
	** if the trace is negative we check for the largest of u1, u2 and u3
	*/

	if (trace > 0.0) {
		root = sqrt(trace + 1.0);                                   // 2*u0
		u0 = 0.5 * root;
		root = 0.5 / root;                                          // 1/(4*u0)
		u1 = (m->m[2][1] - m->m[1][2]) * root;
		u2 = (m->m[0][2] - m->m[2][0]) * root;
		u3 = (m->m[1][0] - m->m[0][1]) * root;
	}
	else if (m->m[0][0] >= m->m[1][1] && m->m[0][0] >= m->m[2][2]) {
		/* first diagonal element is largest */
		root = sqrt(1.0 + m->m[0][0] - (m->m[1][1] + m->m[2][2]));  // 2*u1
		u1 = 0.5 * root;
		root = 0.5 / root;                                          // 1/(4*u1)
		u2 = (m->m[0][1] + m->m[1][0]) * root;
		u3 = (m->m[2][0] + m->m[0][2]) * root;
		u0 = (m->m[2][1] - m->m[1][2]) * root;
	}
	else if (m->m[1][1] >= m->m[2][2]) {
		/* second diagonal element is largest */
		root = sqrt(1.0 + m->m[1][1] - (m->m[2][2] + m->m[0][0]));  // 2*u2
		u2 = 0.5 * root;
		root = 0.5 / root;                                          // 1/(4*u2)
		u3 = (m->m[1][2] + m->m[2][1]) * root;
		u1 = (m->m[0][1] + m->m[1][0]) * root;
		u0 = (m->m[0][2] - m->m[2][0]) * root;
	}
	else {
		/* third diagonal element is largest */
		root = sqrt(1.0 + m->m[2][2] - (m->m[0][0] + m->m[1][1]));  // 2*u3
		u3 = 0.5 * root;
		root = 0.5 / root;                                          // 1/(4*u3)
		u1 = (m->m[2][0] + m->m[0][2]) * root;
		u2 = (m->m[1][2] + m->m[2][1]) * root;
		u0 = (m->m[1][0] - m->m[0][1]) * root;
	}

	/* normalize the quaternion before converting to REAL */
	{
		double norm = sqrt(u0 * u0 + u1 * u1 + u2 * u2 + u3 * u3);

		u0 /= norm;
		u1 /= norm;
		u2 /= norm;
		u3 /= norm;
	}

	/* meet the convention that u0 is always positive */
	if (u0 < 0.0)
	{
		qr->u0 = (REAL)-u0;
		qr->u1 = (REAL)-u1;
		qr->u2 = (REAL)-u2;
		qr->u3 = (REAL)-u3;
	}
	else
	{
		qr->u0 = (REAL)u0;
		qr->u1 = (REAL)u1;
		qr->u2 = (REAL)u2;
		qr->u3 = (REAL)u3;
	}
}

void Nur_Rbt::quaternion_to_rot_matrix(
	const QUATERNION* q,  /* Input quaternion */
	ROT_MATRIX* mr)  /* Output rotation matrix */
{
	double xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;

	xs = q->u1 * 2.0;
	ys = q->u2 * 2.0;
	zs = q->u3 * 2.0;

	wx = q->u0 * xs;
	wy = q->u0 * ys;
	wz = q->u0 * zs;

	xx = q->u1 * xs;
	xy = q->u1 * ys;
	xz = q->u1 * zs;

	yy = q->u2 * ys;
	yz = q->u2 * zs;
	zz = q->u3 * zs;

	mr->m[0][0] = 1.0 - (yy + zz);
	mr->m[0][1] = xy - wz;
	mr->m[0][2] = xz + wy;

	mr->m[1][0] = xy + wz;
	mr->m[1][1] = 1.0 - (xx + zz);
	mr->m[1][2] = yz - wx;

	mr->m[2][0] = xz - wy;
	mr->m[2][1] = yz + wx;
	mr->m[2][2] = 1.0 - (xx + yy);
}

void Nur_Rbt::pose_to_T(POSE* pose, TRANS_MATRIX* T)
{
	int i, j;
	ROT_MATRIX rot = { 0 };
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (i == j)
			{
				T->t[i][j] = 1.f;
			}
			else
			{
				T->t[i][j] = 0.f;
			}
		}
	}

	quaternion_to_rot_matrix(&pose->quat, &rot);

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			T->t[i][j] = rot.m[i][j];
		}
	}

	T->t[0][3] = pose->pos.x;
	T->t[1][3] = pose->pos.y;
	T->t[2][3] = pose->pos.z;


}

REAL Nur_Rbt::sin_ramp_creater(int ramp_len, int idx, REAL* cur, REAL* goal)
{
	REAL ratio = 1.0f;

	ratio = *cur + (*goal - *cur) * (0.5 * sinf(PI / ramp_len * idx - PI_2) + 0.5);

	return (ratio);
}

void Nur_Rbt::calc_j2m(REAL gear, BOOL inv, BOOL is_se, REAL *j1, REAL *j2, REAL *m1, REAL *m2)
{
	REAL n1 = 0.0f;
	REAL n2 = 0.0f;
	if (is_se)
	{
		if (inv)
		{
			n1 = *j1 + 2.0 * *j2;
			n2 = -*j1 + 2.0 * *j2;
		}
		else
		{
			n1 = *j1 + 2.0 * *j2;
			n2 = *j1 - 2.0 * *j2;
		}
	}
	else
	{
		if (inv)
		{
			n1 = *j1 + *j2;
			n2 = -*j1 + *j2;
		}
		else
		{
			n1 = *j1 + *j2;
			n2 = *j1 - *j2;
		}
	}
	
	*m1 = n1 * gear;
	*m2 = n2 * gear;
}

void Nur_Rbt::calc_m2j(REAL gear, BOOL inv, BOOL is_se, REAL *m1, REAL *m2, REAL *j1, REAL *j2)
{
	REAL n1, n2;
	n1 = *m1 / gear;
	n2 = *m2 / gear;
	if (is_se)
	{
		if (inv)
		{
			*j1 = 0.5f * (n1 - n2);
			*j2 = 0.25f * (n1 + n2);
		}
		else
		{
			*j1 = 0.5f * (n1 + n2);
			*j2 = 0.25f * (n1 - n2);
		}
	}
	else
	{
		if (inv)
		{
			*j1 = 0.5f * (n1 - n2);
			*j2 = 0.5f * (n1 + n2);
		}
		else
		{
			*j1 = 0.5f * (n1 + n2);
			*j2 = 0.5f * (n1 - n2);
		}
	}
}

void Nur_Rbt::Euler2quaternion(REAL* C, QUATERNION* qr)
{
	//   Z  Y  X
	REAL X, Y, Z;
	X = C[2];
	Y = C[1];
	Z = C[0];
	qr->u0 = cos(X / 2) * cos(Y / 2) * cos(Z / 2) - sin(X / 2) * sin(Y / 2) * sin(Z / 2);
	qr->u1 = cos(Y / 2) * cos(Z / 2) * sin(X / 2) - cos(X / 2) * sin(Y / 2) * sin(Z / 2);
	qr->u2 = cos(X / 2) * cos(Z / 2) * sin(Y / 2) + cos(Y / 2) * sin(X / 2) * sin(Z / 2);
	qr->u3 = cos(X / 2) * cos(Y / 2) * sin(Z / 2) + cos(Z / 2) * sin(X / 2) * sin(Y / 2);





}
