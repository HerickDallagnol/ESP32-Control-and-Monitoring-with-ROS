#include <ros.h>
#include <std_msgs/Int32.h>
#include <esp32-hal-ledc.h> 

ros::NodeHandle nh;

int pwmChannel = 0;
int frequence = 1000; // 1KHz
int resolution = 8;

const int fan_control = 33;
int count = 0;
unsigned long start_time;
int rpm;
int pwm = 0; // Variável global para armazenar o valor de PWM

void counter() {
  count++;
}

void pwmCallback(const std_msgs::Int32 &PwmReceive) {
  pwm = PwmReceive.data;
  ledcWrite(pwmChannel, pwm);
}

ros::Subscriber<std_msgs::Int32> sub("PwmReceive", &pwmCallback);

void setup() {
  nh.getHardware()->setBaud(9600);

  ledcSetup(pwmChannel, frequence, resolution);
  ledcAttachPin(fan_control, pwmChannel);

  nh.initNode();
  nh.subscribe(sub);

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(32), counter, RISING);
}

void loop() {
  rpm = count * 30;

  Serial.print("PWM = ");
  Serial.print(map(pwm, 0, 255, 0, 100));
  Serial.print("% , vel = ");
  Serial.print(rpm);
  Serial.println(" rpm");

  nh.spinOnce();
}
