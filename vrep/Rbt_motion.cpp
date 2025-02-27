#include"Rbt_motion.h"

rbtmotion::rbtmotion()
{

	for (int i = 0; i < 6; i++)
	{

		rbt.out.fdb_l_value[i] = 0;
		rbt.out.fdb_r_value[i] = 0;
		rbt.out.fdb_pose_l[i] = 0;
		rbt.out.fdb_pose_r[i] = 0;
	}
	
}


output rbtmotion::motion(input1* input)
{
	output out;

	if (input->cmd.prepose_enable == 1)
	{
		nur_rbt.nrbt_data.left.prepose->x = 0.0f;
		nur_rbt.nrbt_data.right.prepose->x = 0.0f;
		nur_rbt.nrbt_data.waist.p_y_k.x = 0.0f;
	}
	this->nur_rbt.nrbt_data.control_mode = input->cmd.Mode;
	for (int i = 0; i < 6; i++)
	{
		this->nur_rbt.nrbt_data.left.fdb_value[i] = input->cmd_value.current_l_value[i];
		this->nur_rbt.nrbt_data.right.fdb_value[i] = input->cmd_value.current_r_value[i];
	}

	{
		this->nur_rbt.nrbt_data.waist.fdb_y_k[0] = input->cmd_value.current_y_value;
		this->nur_rbt.nrbt_data.waist.fdb_y_k[1] = input->cmd_value.current_k_value;
	}
	switch (this->nur_rbt.nrbt_data.control_mode)
	{

	case POSE_CONTROL:
	{
		double suml=0, sumr=0;
		double sumL = 0, sumR = 0;
		REAL temp_step_pos_l[3] = { 0.0f,0.0f,0.0f };
		REAL temp_step_orin_l[3] = { 0.0f,0.0f,0.0f };

		REAL temp_step_pos_r[3] = { 0.0f,0.0f,0.0f };
		REAL temp_step_orin_r[3] = { 0.0f,0.0f,0.0f };
		BOOL is_solution = FALSE;
		for (int i = 0; i < 3; i++)
		{
			suml += fabs(input->cmd_value.pose_l_value[i] - nur_rbt.nrbt_data.left.pose->temp_pose[i]);
			sumr += fabs(input->cmd_value.pose_r_value[i] - nur_rbt.nrbt_data.right.pose->temp_pose[i]);
			suml += fabs(input->cmd_value.pose_l_value[i + 3] - nur_rbt.nrbt_data.left.pose->temp_euler[i]);
			sumL += fabs(input->cmd_value.pose_r_value[i + 3] - nur_rbt.nrbt_data.right.pose->temp_euler[i]);
		}

		if (suml > 0.f || sumL > 0.f)
		{
			this->nur_rbt.nrbt_data.left.pose->ramp_count = 0;
			for (int i = 0; i < 3; i++)
			{
			
				this->nur_rbt.nrbt_data.left.pose->temp_euler[i] = this->nur_rbt.nrbt_data.left.pose->last_euler[i];
				this->nur_rbt.nrbt_data.left.pose->temp_pose[i] = this->nur_rbt.nrbt_data.left.pose->last_pose[i];
			}

		}


		if (sumr > 0.f || sumR > 0.f)
		{
			this->nur_rbt.nrbt_data.right.pose->ramp_count = 0;
			for (int i = 0; i < 3; i++)
			{
			
				this->nur_rbt.nrbt_data.right.pose->temp_euler[i] = this->nur_rbt.nrbt_data.right.pose->last_euler[i];
				this->nur_rbt.nrbt_data.right.pose->temp_pose[i] = this->nur_rbt.nrbt_data.right.pose->last_pose[i];
			}

		}



		if (this->nur_rbt.nrbt_data.left.pose->ramp_count <= this->nur_rbt.nrbt_data.left.pose->ramp_len)
		{


			for (int i = 0; i < 3; i++)
			{
				this->nur_rbt.nrbt_data.left.pose->ramp_pose[i] = this->nur_rbt.sin_ramp_creater(this->nur_rbt.nrbt_data.left.pose->ramp_len,
					this->nur_rbt.nrbt_data.left.pose->ramp_count, &this->nur_rbt.nrbt_data.left.pose->temp_pose[i], &input->cmd_value.pose_l_value[i]);

				this->nur_rbt.nrbt_data.left.pose->ramp_euler[i] = this->nur_rbt.sin_ramp_creater(this->nur_rbt.nrbt_data.left.pose->ramp_len,
					this->nur_rbt.nrbt_data.left.pose->ramp_count, &this->nur_rbt.nrbt_data.left.pose->temp_euler[i], &input->cmd_value.pose_l_value[i + 3]);
			}
			this->nur_rbt.nrbt_data.left.pose->ramp_count++;
		}

		if (this->nur_rbt.nrbt_data.right.pose->ramp_count <= this->nur_rbt.nrbt_data.right.pose->ramp_len)
		{


			for (int i = 0; i < 3; i++)
			{
				this->nur_rbt.nrbt_data.right.pose->ramp_pose[i] = this->nur_rbt.sin_ramp_creater(this->nur_rbt.nrbt_data.right.pose->ramp_len,
					this->nur_rbt.nrbt_data.right.pose->ramp_count, &this->nur_rbt.nrbt_data.right.pose->temp_pose[i], &input->cmd_value.pose_r_value[i]);

				this->nur_rbt.nrbt_data.right.pose->ramp_euler[i] = this->nur_rbt.sin_ramp_creater(this->nur_rbt.nrbt_data.right.pose->ramp_len,
					this->nur_rbt.nrbt_data.right.pose->ramp_count, &this->nur_rbt.nrbt_data.right.pose->temp_euler[i], &input->cmd_value.pose_r_value[i + 3]);
			}

			this->nur_rbt.nrbt_data.right.pose->ramp_count++;
		}


		for (int i = 0; i < 3; i++)
		{

			this->nur_rbt.nrbt_data.left.pose->last_pose[i] = input->cmd_value.pose_l_value[i];
			this->nur_rbt.nrbt_data.left.pose->last_euler[i] = input->cmd_value.pose_l_value[i + 3];
			temp_step_pos_l[i] = this->nur_rbt.nrbt_data.left.pose->ramp_pose[i] * 0.5f;
			temp_step_orin_l[i] = this->nur_rbt.nrbt_data.left.pose->ramp_euler[i] * d2r / 10;

			this->nur_rbt.nrbt_data.right.pose->last_pose[i] = input->cmd_value.pose_r_value[i];
			this->nur_rbt.nrbt_data.right.pose->last_euler[i] = input->cmd_value.pose_r_value[i + 3];
			temp_step_pos_r[i] = this->nur_rbt.nrbt_data.right.pose->ramp_pose[i] * 0.05f;
			temp_step_orin_r[i] = this->nur_rbt.nrbt_data.right.pose->ramp_euler[i] * d2r / 10;


		}
		nur_rbt.fkine_Rbt_DH_jog(this->nur_rbt.nrbt_data.left.T_base, this->nur_rbt.nrbt_data.left.fdb_value,
			this->nur_rbt.nrbt_data.left.DH, temp_step_pos_l, temp_step_orin_l,&this->nur_rbt.nrbt_data.left.dT);

		nur_rbt.fkine_Rbt_DH_jog(this->nur_rbt.nrbt_data.right.T_base, this->nur_rbt.nrbt_data.right.fdb_value,
			this->nur_rbt.nrbt_data.right.DH, temp_step_pos_r, temp_step_orin_r, &this->nur_rbt.nrbt_data.right.dT);


		is_solution = nur_rbt.ikine_IteraFcn2(this->nur_rbt.nrbt_data.left.T_base,this->nur_rbt.nrbt_data.left.DH, &this->nur_rbt.nrbt_data.left.dT,
			this->nur_rbt.nrbt_data.left.fdb_value, nur_rbt.nrbt_data.left.out_value);
		is_solution = nur_rbt.ikine_IteraFcn2(this->nur_rbt.nrbt_data.right.T_base, this->nur_rbt.nrbt_data.right.DH, &this->nur_rbt.nrbt_data.right.dT,
			this->nur_rbt.nrbt_data.right.fdb_value, nur_rbt.nrbt_data.right.out_value);
		
	
	}

	break;

	case JOINT_CONTROL:
	{
		
		for (int i = 0; i < 6; i++)
		{
			if (fabs(input->cmd_value.jog_l_value[i] - this->nur_rbt.nrbt_data.left.joint.last_step[i]) > 0.08f)
			{
				this->nur_rbt.nrbt_data.left.joint.ramp_joint[i] = 0;
				this->nur_rbt.nrbt_data.left.joint.temp_step[i] = this->nur_rbt.nrbt_data.left.joint.last_step[i];
				nur_rbt.nrbt_data.left.joint.ramp_count[i] = 0;
			}
			if (fabs(input->cmd_value.jog_r_value[i] - this->nur_rbt.nrbt_data.right.joint.last_step[i]) > 0.0f)
			{
				
				this->nur_rbt.nrbt_data.right.joint.ramp_joint[i] = 0;
				this->nur_rbt.nrbt_data.right.joint.temp_step[i] = this->nur_rbt.nrbt_data.right.joint.last_step[i];
				nur_rbt.nrbt_data.right.joint.ramp_count[i] = 0;
			}
		}

		{
			if (fabs(input->cmd_value.jog_y_value - this->nur_rbt.nrbt_data.waist.i_y_k.last_step[0]) > 0.08f)
			{
				this->nur_rbt.nrbt_data.waist.i_y_k.ramp_joint[0] = 0;
				this->nur_rbt.nrbt_data.waist.i_y_k.temp_step[0] = this->nur_rbt.nrbt_data.waist.i_y_k.last_step[0];
				this->nur_rbt.nrbt_data.waist.i_y_k.ramp_count[0] = 0;
			}

			if (fabs(input->cmd_value.jog_k_value - this->nur_rbt.nrbt_data.waist.i_y_k.last_step[1]) > 0.08f)
			{
				this->nur_rbt.nrbt_data.waist.i_y_k.ramp_joint[1] = 0;
				this->nur_rbt.nrbt_data.waist.i_y_k.temp_step[1] = this->nur_rbt.nrbt_data.waist.i_y_k.last_step[1];
				this->nur_rbt.nrbt_data.waist.i_y_k.ramp_count[1] = 0;
			}
		}


		{
		
		
			if (this->nur_rbt.nrbt_data.waist.i_y_k.ramp_count[0] <= nur_rbt.nrbt_data.waist.i_y_k.ramp_len)
			{

				nur_rbt.nrbt_data.waist.i_y_k.ramp_joint[0]= this->nur_rbt.sin_ramp_creater(nur_rbt.nrbt_data.waist.i_y_k.ramp_len, nur_rbt.nrbt_data.waist.i_y_k.ramp_count[0],
					&this->nur_rbt.nrbt_data.waist.i_y_k.temp_step[0], &input->cmd_value.jog_y_value);
				
			}
			nur_rbt.nrbt_data.waist.i_y_k.ramp_count[0]++;
			if (this->nur_rbt.nrbt_data.waist.i_y_k.ramp_count[1] <= nur_rbt.nrbt_data.waist.i_y_k.ramp_len)
			{

				nur_rbt.nrbt_data.waist.i_y_k.ramp_joint[1] = this->nur_rbt.sin_ramp_creater(nur_rbt.nrbt_data.waist.i_y_k.ramp_len, nur_rbt.nrbt_data.waist.i_y_k.ramp_count[1],
					&this->nur_rbt.nrbt_data.waist.i_y_k.temp_step[1], &input->cmd_value.jog_k_value);
				
			}
			nur_rbt.nrbt_data.waist.i_y_k.ramp_count[1]++;
		}
		for (int i = 0; i < 6; i++)
		{
			//if (flag1[i])
			{
				if (nur_rbt.nrbt_data.left.joint.ramp_count[i] <= nur_rbt.nrbt_data.left.joint.ramp_len)
				{
					nur_rbt.nrbt_data.left.joint.ramp_joint[i] = this->nur_rbt.sin_ramp_creater(nur_rbt.nrbt_data.left.joint.ramp_len, nur_rbt.nrbt_data.left.joint.ramp_count[i],
						&this->nur_rbt.nrbt_data.left.joint.temp_step[i], &input->cmd_value.jog_l_value[i]);
				}
				nur_rbt.nrbt_data.left.joint.ramp_count[i]++;
			}

			//if (flag2[i])
			{
				if (nur_rbt.nrbt_data.right.joint.ramp_count[i] <= nur_rbt.nrbt_data.right.joint.ramp_len)
				{
					nur_rbt.nrbt_data.right.joint.ramp_joint[i] = this->nur_rbt.sin_ramp_creater(nur_rbt.nrbt_data.right.joint.ramp_len, nur_rbt.nrbt_data.right.joint.ramp_count[i],
						&this->nur_rbt.nrbt_data.right.joint.temp_step[i], &input->cmd_value.jog_r_value[i]);
				}
				nur_rbt.nrbt_data.right.joint.ramp_count[i]++;
			}
		}
		for (int i = 0; i < 6; i++)
		{
			nur_rbt.nrbt_data.left.out_value[i] = nur_rbt.nrbt_data.left.fdb_value[i] +
				nur_rbt.nrbt_data.left.joint.ramp_joint[i] * d2r / 100;

			nur_rbt.nrbt_data.right.out_value[i] = nur_rbt.nrbt_data.right.fdb_value[i] +
				nur_rbt.nrbt_data.right.joint.ramp_joint[i] * d2r / 100;

			nur_rbt.nrbt_data.left.joint.last_step[i] = input->cmd_value.jog_l_value[i];
			nur_rbt.nrbt_data.right.joint.last_step[i] = input->cmd_value.jog_r_value[i];
		}

		{
			
			nur_rbt.nrbt_data.waist.out_y_k[0] = nur_rbt.nrbt_data.waist.fdb_y_k[0] + nur_rbt.nrbt_data.waist.i_y_k.ramp_joint[0] * d2r / 100;
			nur_rbt.nrbt_data.waist.out_y_k[1] = nur_rbt.nrbt_data.waist.fdb_y_k[1] + nur_rbt.nrbt_data.waist.i_y_k.ramp_joint[1] * d2r / 100; 
			nur_rbt.nrbt_data.waist.i_y_k.last_step[0] = input->cmd_value.jog_y_value;
			nur_rbt.nrbt_data.waist.i_y_k.last_step[1] = input->cmd_value.jog_k_value;
		
		}

	}
	break;
	case PRE_POS_CONTROL:
	{

		double L_index1 = 0.0f;
		double L_index2 = 0.0f;
		double temp_norm1 = 0.0f;
		double temp_norm2 = 0.0f;
		double L_indexy = 0.0f;
		double temp_normy = 0.0f;
	
		if (nur_rbt.nrbt_data.waist.p_y_k.x < 0.08f)
		{


			for (int i = 0; i < 2; i++)
			{

				{
					if (i == 0)
					{
						nur_rbt.nrbt_data.waist.p_y_k.init_joint[i] = input->cmd_value.current_y_value;
						nur_rbt.nrbt_data.waist.p_y_k.goal_joint[i] = input->cmd_value.prepose_y_value;
						nur_rbt.nrbt_data.waist.p_y_k.dq[i] = nur_rbt.nrbt_data.waist.p_y_k.goal_joint[i] - nur_rbt.nrbt_data.waist.p_y_k.init_joint[i];
					}
					else
					{

						nur_rbt.nrbt_data.waist.p_y_k.init_joint[i] = input->cmd_value.current_k_value;
						nur_rbt.nrbt_data.waist.p_y_k.goal_joint[i] = input->cmd_value.prepose_k_value;
						nur_rbt.nrbt_data.waist.p_y_k.dq[i] = nur_rbt.nrbt_data.waist.p_y_k.goal_joint[i] - nur_rbt.nrbt_data.waist.p_y_k.init_joint[i];
					}
					

				}
			}

			nur_rbt.nrbt_data.waist.p_y_k.norm= nur_rbt.norm_array(nur_rbt.nrbt_data.waist.p_y_k.dq, 2);
		
		}
		if (nur_rbt.nrbt_data.waist.p_y_k.norm > 0.05f)
		{

			for (int i = 0; i < 2; i++)
			{
				if (i == 0)
					nur_rbt.nrbt_data.waist.p_y_k.temp_dq[i] = input->cmd_value.current_y_value - nur_rbt.nrbt_data.waist.p_y_k.init_joint[i];
				else
				{
					nur_rbt.nrbt_data.waist.p_y_k.temp_dq[i] = input->cmd_value.current_k_value - nur_rbt.nrbt_data.waist.p_y_k.init_joint[i];

				}
			}
			temp_normy = nur_rbt.norm_array(nur_rbt.nrbt_data.waist.p_y_k.temp_dq, 2);
			L_indexy = temp_normy / nur_rbt.nrbt_data.waist.p_y_k.norm;
			if ((nur_rbt.nrbt_data.waist.p_y_k.y - L_indexy) < 0.02f)
			{
				nur_rbt.nrbt_data.waist.p_y_k.x = nur_rbt.nrbt_data.waist.p_y_k.x + 0.02;

			}

			if (nur_rbt.nrbt_data.waist.p_y_k.x > 1.0f)
			{
				nur_rbt.nrbt_data.waist.p_y_k.x = 1.0f;

			}
			else
			{

				nur_rbt.nrbt_data.waist.p_y_k.y = nur_rbt.lspb_plan(1.5, nur_rbt.nrbt_data.waist.p_y_k.x);
				for (int i = 0; i < 2; i++)
				{
					nur_rbt.nrbt_data.waist.out_y_k[i] = nur_rbt.nrbt_data.waist.p_y_k.init_joint[i] + nur_rbt.nrbt_data.waist.p_y_k.y * nur_rbt.nrbt_data.waist.p_y_k.dq[i];
				}
			}
		 
		}
		else
		{

			nur_rbt.nrbt_data.waist.out_y_k[0] = input->cmd_value.current_y_value;
			nur_rbt.nrbt_data.waist.out_y_k[1] = input->cmd_value.current_k_value;
		}
		
		if (nur_rbt.nrbt_data.left.prepose->x < 0.08f)
		{
			for (int i = 0; i < 6; i++)
			{
				nur_rbt.nrbt_data.left.prepose->init_joint[i] = input->cmd_value.current_l_value[i];
				nur_rbt.nrbt_data.left.prepose->goal_joint[i] = input->cmd_value.prepose_l_value[i];
				nur_rbt.nrbt_data.left.prepose->dq[i] = nur_rbt.nrbt_data.left.prepose->goal_joint[i] - nur_rbt.nrbt_data.left.prepose->init_joint[i];
			}
			nur_rbt.nrbt_data.left.prepose->norm = nur_rbt.norm_array(nur_rbt.nrbt_data.left.prepose->dq, 6);
		}
		if (nur_rbt.nrbt_data.left.prepose->norm > 0.05f)
		{
			for (int i = 0; i < 6; i++)
			{
				nur_rbt.nrbt_data.left.prepose->temp_dq[i] = nur_rbt.nrbt_data.left.fdb_value[i] - nur_rbt.nrbt_data.left.prepose->init_joint[i];
			}
			temp_norm1 = nur_rbt.norm_array(nur_rbt.nrbt_data.left.prepose->temp_dq, 6);
			L_index1 = temp_norm1 / nur_rbt.nrbt_data.left.prepose->norm;
			if ((nur_rbt.nrbt_data.left.prepose->y - L_index1) < 0.02f)
			{
				nur_rbt.nrbt_data.left.prepose->x = nur_rbt.nrbt_data.left.prepose->x + 0.02;

			}

			if (nur_rbt.nrbt_data.left.prepose->x > 1.0f)
			{
				nur_rbt.nrbt_data.left.prepose->x = 1.0f;
			}
			else
			{
				nur_rbt.nrbt_data.left.prepose->y = nur_rbt.lspb_plan(1.5, nur_rbt.nrbt_data.left.prepose->x);
				for (int i = 0; i < 6; i++)
				{
					nur_rbt.nrbt_data.left.out_value[i] = nur_rbt.nrbt_data.left.prepose->init_joint[i] + nur_rbt.nrbt_data.left.prepose->y * nur_rbt.nrbt_data.left.prepose->dq[i];
				}
			}
		}
		else
		{
			for (int i = 0; i < 6; i++)
			{
				nur_rbt.nrbt_data.left.out_value[i] = nur_rbt.nrbt_data.left.fdb_value[i];
			}
		}
		if (nur_rbt.nrbt_data.right.prepose->x < 0.08f)
		{
			for (int i = 0; i < 6; i++)
			{
				nur_rbt.nrbt_data.right.prepose->init_joint[i] = input->cmd_value.current_r_value[i];
				nur_rbt.nrbt_data.right.prepose->goal_joint[i] = input->cmd_value.prepose_r_value[i];
				nur_rbt.nrbt_data.right.prepose->dq[i] = nur_rbt.nrbt_data.right.prepose->goal_joint[i] - nur_rbt.nrbt_data.right.prepose->init_joint[i];
			}
			nur_rbt.nrbt_data.right.prepose->norm = nur_rbt.norm_array(nur_rbt.nrbt_data.right.prepose->dq, 6);
		}
		if (nur_rbt.nrbt_data.right.prepose->norm > 0.05f)
		{
			for (int i = 0; i < 6; i++)
			{
				nur_rbt.nrbt_data.right.prepose->temp_dq[i] = nur_rbt.nrbt_data.right.fdb_value[i] - nur_rbt.nrbt_data.right.prepose->init_joint[i];

			}
			temp_norm1 = nur_rbt.norm_array(nur_rbt.nrbt_data.right.prepose->temp_dq, 6);
			L_index1 = temp_norm1 / nur_rbt.nrbt_data.right.prepose->norm;
			if ((nur_rbt.nrbt_data.right.prepose->y - L_index1) < 0.02f)
			{
				nur_rbt.nrbt_data.right.prepose->x = nur_rbt.nrbt_data.right.prepose->x + 0.02;

			}

			if (nur_rbt.nrbt_data.right.prepose->x > 1.0f)
			{
				nur_rbt.nrbt_data.right.prepose->x = 1.0f;

			}
			else
			{
				nur_rbt.nrbt_data.right.prepose->y = nur_rbt.lspb_plan(1.5, nur_rbt.nrbt_data.right.prepose->x);


				for (int i = 0; i < 6; i++)
				{

					nur_rbt.nrbt_data.right.out_value[i] = nur_rbt.nrbt_data.right.prepose->init_joint[i] + nur_rbt.nrbt_data.right.prepose->y * nur_rbt.nrbt_data.right.prepose->dq[i];

				}
			}

		}
		else
		{

			for (int i = 0; i < 6; i++)
			{
				nur_rbt.nrbt_data.right.out_value[i] = nur_rbt.nrbt_data.right.fdb_value[i];
			}


		}


	}
	break;
	default:
		for (int i = 0; i < 6; i++)
		{
			nur_rbt.nrbt_data.left.out_value[i]=nur_rbt.nrbt_data.left.fdb_value[i];
			nur_rbt.nrbt_data.right.out_value[i] = nur_rbt.nrbt_data.right.out_value[i];
		}
		nur_rbt.nrbt_data.waist.out_y_k[0] = nur_rbt.nrbt_data.waist.fdb_y_k[0];
		nur_rbt.nrbt_data.waist.out_y_k[1] = nur_rbt.nrbt_data.waist.fdb_y_k[1];
		break;
	}
 
	for (int i = 0; i < 6; i++)
	{
		out.fdb_l_value[i] = nur_rbt.nrbt_data.left.out_value[i];
		out.fdb_r_value[i] = nur_rbt.nrbt_data.right.out_value[i];
		
	}


	TRANS_MATRIX POSE[2] = {0};
	this->nur_rbt.fkine_Rbt_DH(this->nur_rbt.nrbt_data.left.T_base, out.fdb_l_value, this->nur_rbt.nrbt_data.left.DH, &POSE[0]);
	this->nur_rbt.fkine_Rbt_DH(this->nur_rbt.nrbt_data.right.T_base, out.fdb_r_value, this->nur_rbt.nrbt_data.right.DH, &POSE[1]);

	double l[6] = {0};
	double r[6] = {0};
	for (int i = 0; i < 3; i++)
	{

		l[i] = POSE[0].t[i][3];
		r[i] = POSE[1].t[i][3];
	}
	ROT_MATRIX POSE_POSE[2] = {0};
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{

			POSE_POSE[0].m[i][j] = POSE[0].t[i][j];
			POSE_POSE[1].m[i][j] = POSE[1].t[i][j];
		}
	}
	double L[3] = {0};
	double R[3] = {0};
	this->nur_rbt.rotm2zyxEuler(POSE_POSE[0], L);
	this->nur_rbt.rotm2zyxEuler(POSE_POSE[1], R);
	for (int i = 0; i < 3; i++)
	{


		l[i+3] = L[2 - i];
		r[i+3] = R[2 - i];
	}
	for (int i = 0; i < 6; i++)
	{
		out.fdb_pose_l[i] = l[i];
		out.fdb_pose_r[i] = r[i];
	}
	
	out.fdb_y_value = nur_rbt.nrbt_data.waist.out_y_k[0];
	out.fdb_k_value = nur_rbt.nrbt_data.waist.out_y_k[1];
	for (int i = 0; i < JNT_NUM; i = i + 2)
	{
		if (i < 1)
			this->nur_rbt.calc_j2m((REAL)2400, TRUE, TRUE, &out.fdb_l_value[i], &out.fdb_l_value[i + 1], &out.fdb_l_cmt_value[i], &out.fdb_l_cmt_value[i + 1]);
		else
			this->nur_rbt.calc_j2m((REAL)3060, TRUE, FALSE, &out.fdb_l_value[i], &out.fdb_l_value[i + 1], &out.fdb_l_cmt_value[i], &out.fdb_l_cmt_value[i + 1]);
	}
	for (int i = 0; i < JNT_NUM; i = i + 2)
	{
		if (i < 1)
			this->nur_rbt.calc_j2m((REAL)2400, TRUE, TRUE, &out.fdb_r_value[i], &out.fdb_r_value[i + 1], &out.fdb_r_cmt_value[i], &out.fdb_r_cmt_value[i + 1]);
		else
			this->nur_rbt.calc_j2m((REAL)3060, TRUE, FALSE, &out.fdb_r_value[i], &out.fdb_r_value[i + 1], &out.fdb_r_cmt_value[i], &out.fdb_r_cmt_value[i + 1]);
	}
		return out;
}
