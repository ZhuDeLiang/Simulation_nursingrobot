#include<iostream>
#include<sstream>
#include"extApi.h"
#include<windows.h>
#include<nur_rbt_interface.h>
#include<rbt_math.h>
#include<Rbt_motion.h>


#define PI 3.14
#define TRUE 1
#define Speed 0.05
using namespace std;
int port = 20000;
int pjoint_handle[14];
std::ostringstream out;
std::string str = "b";
HANDLE hamper;
prbt_data input;
simxFloat fdb_joint[14] = {0};
simxFloat goal_joint[14] = { 0 };
simxFloat send_joint[12] = { 0 };
simxFloat step_Joint[12] = { 0 };
double current_joint_j[12];
simxFloat  current_joint[12];
double current_joint_goal_j[12];
int step[12] = {1,1,1,1,1,1,1,1,1,1,1,1};
int t[12];
int index[12];

REAL  sin_ramp_creater(int ramp_len, int idx, REAL* cur, REAL* goal)
{
	REAL ratio = 1.0f;

	ratio = *cur + (*goal - *cur) * (0.5 * sinf((idx*PI) / ramp_len  - PI_2) + 0.5);

	return (ratio);
}
int main()
{
	rbtmotion rbt;

	hamper = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, "data");
	if (!hamper)
	{

	std:; cout << "Not open shared memory" << std::endl;
		return 0;
	}
	input = (prbt_data)MapViewOfFile(hamper, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (input==NULL)
	{

	std::cout << "open fail" << std::endl;

	}

	int clientID = simxStart("127.0.0.1", port, 1, 1, 3000, 5);
	if (clientID !=-1)
	{
		std::cout << "connect" << endl;
		

		int a=simxGetObjectHandle(clientID, "b1", &pjoint_handle[0], simx_opmode_blocking);
	std:: cout <<a<< endl;
		simxGetObjectHandle(clientID, "b2", &pjoint_handle[1], simx_opmode_blocking);

		simxGetObjectHandle(clientID, "l1", &pjoint_handle[2], simx_opmode_blocking);
		simxGetObjectHandle(clientID, "l2", &pjoint_handle[3], simx_opmode_blocking);
		simxGetObjectHandle(clientID, "l3", &pjoint_handle[4], simx_opmode_blocking);
		simxGetObjectHandle(clientID, "l4", &pjoint_handle[5], simx_opmode_blocking);
		simxGetObjectHandle(clientID, "l5", &pjoint_handle[6], simx_opmode_blocking);
		simxGetObjectHandle(clientID, "l6", &pjoint_handle[7], simx_opmode_blocking);

		simxGetObjectHandle(clientID, "r1", &pjoint_handle[8], simx_opmode_blocking);
		simxGetObjectHandle(clientID, "r2", &pjoint_handle[9], simx_opmode_blocking);
		simxGetObjectHandle(clientID, "r3", &pjoint_handle[10], simx_opmode_blocking);
		simxGetObjectHandle(clientID, "r4", &pjoint_handle[11], simx_opmode_blocking);
		simxGetObjectHandle(clientID, "r5", &pjoint_handle[12], simx_opmode_blocking);
	    simxGetObjectHandle(clientID, "r6", &pjoint_handle[13], simx_opmode_blocking);
	
	}

	else
	{
	std::cout << "Disconnect" << std::endl;
		return 0;
		simxFinish(clientID);

	}
	
	simxSetFloatingParameter(clientID, sim_floatparam_simulation_time_step, 100, simx_opmode_oneshot);
	simxSynchronous(clientID, TRUE);
	simxStartSimulation(clientID, simx_opmode_oneshot);
	int c = 0;
	while (1)
	{

		memcpy(&rbt.rbt.in,&input->in, sizeof(input->in));
		for (int i = 0; i < 14; i++)
		{
			simxGetJointPosition(clientID, pjoint_handle[i], &fdb_joint[i], simx_opmode_oneshot);
		}
		if (c == 0)
		{
			Sleep(100);
			c = 1;
		}
		
		{
			rbt.rbt.in.cmd_value.current_y_value = fdb_joint[0];
			rbt.rbt.in.cmd_value.current_k_value = fdb_joint[1];
		}
		for (int i = 0; i < 6; i++)
		{
			rbt.rbt.in.cmd_value.current_l_value[i] = fdb_joint[i+2 ];
			rbt.rbt.in.cmd_value.current_r_value[i] = fdb_joint[i + 8];
		}

		rbt.rbt.out = rbt.motion(&rbt.rbt.in);
		{
			simxSetJointPosition(clientID, pjoint_handle[0], rbt.rbt.out.fdb_y_value, simx_opmode_oneshot);
			simxSetJointPosition(clientID, pjoint_handle[1], rbt.rbt.out.fdb_k_value, simx_opmode_oneshot);
			/*std::cout << "yyy" << rbt.rbt.out.fdb_y_value << endl;
			std::cout << "kkk" << rbt.rbt.out.fdb_k_value << endl;*/
		}
		for (int i = 0; i < 6; i++)
		{
			/*rbt.rbt.out.fdb_l_value[i] = (simxFloat)rbt.rbt.out.fdb_l_value[i];
			rbt.rbt.out.fdb_r_value[i] = (simxFloat)rbt.rbt.out.fdb_r_value[i];*/
		/*	std::cout << rbt.rbt.out.fdb_l_value[i] << endl;
			std::cout << rbt.rbt.out.fdb_r_value[i] << endl;*/
			simxSetJointPosition(clientID, pjoint_handle[i + 2], rbt.rbt.out.fdb_l_value[i], simx_opmode_oneshot);
			simxSetJointPosition(clientID, pjoint_handle[i + 8], rbt.rbt.out.fdb_r_value[i], simx_opmode_oneshot);
		}
		
		memcpy(&input->out, &rbt.rbt.out, sizeof(rbt.rbt.out));

		for (int i = 0; i < 1; i++)
		{

			std::cout << rbt.rbt.in.cmd_value.pose_l_value[i] << endl;
		}

             
	}


	return 0;

}

		//if (input->in.cmd.Mode == 1)
		//{
	 //    	for (int i = 0; i < 6; i++)
		//    {

		//	step_Joint[i] = input->in.cmd_value.jog_l_value[i];
		//	step_Joint[i+6] = input->in.cmd_value.jog_r_value[i];
		//	step_Joint[i] = step_Joint[i] *( PI / 180) /10;
		//	std::cout << "STEP            "<<step_Joint[i] << endl;
		//	simxGetJointPosition(clientID, pjoint_handle[i+2], &fdb_joint[i+2], simx_opmode_oneshot);
		//	std::cout << fdb_joint[i] << endl;
		//	goal_joint[i] = fdb_joint[i+2] + step_Joint[i];
		//	if (fabs(step_Joint[i])>0.08)
		//	{
		//		simxSetJointPosition(clientID, pjoint_handle[i+2], goal_joint[i], simx_opmode_oneshot);
		//	}
		//		

	

	 //    	}

		//}
	


		//if (input->in.cmd.Mode == 2)
		//{
		//	
		//	for (int i = 0; i < 6; i++)
		//	{
		//		goal_joint[i] = input->in.cmd_value.prepose_l_value[i];
		//		goal_joint[i + 6] = input->in.cmd_value.prepose_r_value[i];

		//	}
		//	for (int i = 0; i < 12; i++)
		//	{
		//	

		//		if (step[i] == 1)
		//		{
		//			
		//			std::cout << "gaol_joint" << i << "           " << goal_joint[i] << std::endl;
		//			simxGetJointPosition(clientID, pjoint_handle[i + 2], &fdb_joint[i + 2], simx_opmode_oneshot);
		//			current_joint_j[i] = fdb_joint[i + 2];
		//			current_joint_goal_j[i] = goal_joint[i];
		//			/*std::cout << fdb_joint[i] << std::endl;*/
		//			
		//			std::cout << "current_joint" << i << "                                                      " << fdb_joint[i] << std::endl;
		//		}
		//	}
		//		for (int i = 0; i < 12; i++)
		//		{
		//		
		//		
		//		if (fabs(current_joint_goal_j[i] - current_joint_j[i]) > 1e-2)

		//		{


		//			t[i] = fabs(current_joint_goal_j[i] - current_joint_j[i]) / Speed;
		//			index[i] = t[i] / 0.1;
		//			std::cout << "index" << i << "                                                              " << index[i] << std::endl;
		//			if (step[i] <= index[i])
		//			{
		//				send_joint[i] = sin_ramp_creater(index[i], step[i], &current_joint_j[i], &current_joint_goal_j[i]);
		//				simxSetJointPosition(clientID, pjoint_handle[i+2], send_joint[i+2], simx_opmode_oneshot);
		//				simxGetJointPosition(clientID, pjoint_handle[i+2], &current_joint[i], simx_opmode_oneshot);
		//				if (current_joint[i] == send_joint[i+2])
		//				{
		//					step[i]++;
		//				}


		//				if (step[i] == index[i] - 1)
		//				{

		//					step[i] = 1;
		//					index[i] = 0;
		//				}

		//			}



		//		}
		//		}


		//	

		//}

	/*while (1)
	{
		for(int a=0;a<12;a++)
		{ 
		
		}
		
	

			for (int i = 0; i < 12; i++)
			{

				std::cout << fdb_joint[i] << std::endl;




				if (fdb_joint[i] != goal_joint[i])
				{
					
					current_joint_j[i] = fdb_joint[i];
					current_joint_goal_j[i] = goal_joint[i];
					

					for(int g=0;g<100;g++)
					{
						send_joint[i] = sin_ramp_creater(100, step[i], &current_joint_j[i], &current_joint_goal_j[i]);
						simxSetJointPosition(clientID, pjoint_handle[i], send_joint[i], simx_opmode_oneshot);

						step[i]++;
					}
					step[i] = 1;
					

				}



				*/



		

	//	}
	//	
	//		

	//	
	//	


	//}


