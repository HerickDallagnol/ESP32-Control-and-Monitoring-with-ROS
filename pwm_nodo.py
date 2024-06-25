#!/usr/bin/env python3
import rospy
from std_msgs.msg import Int32

def enviar_pwm():
    rospy.init_node('enviar_pwm', anonymous=True)
    pub = rospy.Publisher('PwmReceive', Int32, queue_size=10)
    rate = rospy.Rate(1) 

    valor_pwm = 150

    while not rospy.is_shutdown():
        pub.publish(valor_pwm)
        rospy.loginfo("PWM: %d", valor_pwm) # valor PWM entre 0 e 255 
        rate.sleep()

if __name__ == '__main__':
    try:
        enviar_pwm()
    except rospy.ROSInterruptException:
        pass