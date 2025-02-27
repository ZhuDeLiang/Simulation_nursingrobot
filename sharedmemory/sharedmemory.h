#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H
#include <QThread>
#include<qtimer.h>
#include<QSharedMemory>

typedef enum
{
    POSE_CONTROL = 1,
    JOINT_CONTROL = 2,
    SLAVE_CONTROL = 3,
    PRE_POS_CONTROL = 4,
}CONTROL_MODE;
typedef struct
{
    int Enable;
    CONTROL_MODE Mode;
    int arm_r_enable;
    int arm_l_enable;
    int prepose_enable;
    int waist_enable;

}Cmd;

typedef struct
{
    double jog_l_value[6];
    double jog_r_value[6];
    double pose_l_value[6];
    double pose_r_value[6];
    double prepose_l_value[6];
    double prepose_r_value[6];
    double current_l_value[6];
    double current_r_value[6];
    double jog_y_value;
    double jog_k_value;
    double prepose_y_value;
    double prepose_k_value;
    double current_k_value;
    double current_y_value;


}Cmd_value;
typedef struct
{

    Cmd cmd;
    Cmd_value cmd_value;



}input1;


typedef struct
{
    double fdb_r_value[6];
    double fdb_l_value[6];
    double fdb_r_cmt_value[6];
    double fdb_l_cmt_value[6];
    double fdb_y_value;
    double fdb_k_value;
    double  fdb_pose_r[6];
    double  fdb_pose_l[6];
}output;
typedef struct
{

    input1 in;
    output out;
}rbt_data, * prbt_data;
;

class wthread:public QObject
{

public:

    void memory_init();
    void send();
    rbt_data  input;
    rbt_data  *da;
    int condition=0;

};

#endif // SHAREDMEMORY_H
