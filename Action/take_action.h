#ifndef __TAKE__ACTION_H
#define __TAKE__ACTION_H

//#include "stdint.h"
//#include "string.h"
#include "stm32f4xx_tim.h"


// 结构暂时显示放在头文件，refactor结束后，根据可见性调整其位置   SiJY 26-4-14
// 方向定义
typedef enum {
    DIR_CW = 0,     // 顺时针
    DIR_CCW = 1     // 逆时针
}MotorDirection;

typedef enum {
    STATE_STOP = 0,
    STATE_ACCEL = 1,
    STATE_RUN = 2,
    STATE_DECEL = 3
}MotorRunState;

typedef struct {
    TIM_TypeDef *tim;              // 定时器
    uint32_t tim_clock;            // 定时器时钟
    uint16_t tim_irq;              // 定时器中断
    GPIO_TypeDef *pwm_port;        // PWM端口
    uint16_t pwm_pin;              // PWM引脚
    uint8_t pwm_af;                // PWM引脚复用功能
    GPIO_TypeDef *dir_port;        // 方向控制端口
    uint16_t dir_pin;              // 方向控制引脚
    int32_t *step_position;        // 步数位置指针
    void (*step_counter)(signed char);  // 步数计数函数
    void (*dir_control)(uint8_t);  // 方向控制函数
} MotorConfig;

// 速度斜坡数据结构体
typedef struct {
    MotorDirection dir;            // 方向
    MotorRunState run_state;       // 运行状态
    int32_t step_delay;            // 步骤延迟
    int32_t min_delay;             // 最小延迟
    int32_t accel_count;           // 加速度计数
    int32_t decel_val;             // 减速值
    int32_t decel_start;           // 减速开始点
} SpeedRampData;


// 电机控制结构体
typedef struct {
    MotorConfig config;            // 电机配置
    SpeedRampData speed_data;      // 速度数据
    uint32_t accel;                // 加速度
    uint32_t decel;                // 减速度
    uint32_t speed;                // 速度
} MotorControl;

void motor_action_PWM_init(MotorControl *act_cfg);
void motor_TIM_IRQHandler(MotorControl *act_cfg);
void motor_action_move(MotorControl *act_cfg, int step, uint32_t accel, uint32_t decel, uint32_t speed);
void motor_speed_decision(MotorControl *act_cfg);
void motor_step_counter(MotorControl *act_cfg, signed char inc);
void motor_action_dir(MotorControl *act_cfg, uint8_t a);

#endif  // __TAKE__ACTION_H
