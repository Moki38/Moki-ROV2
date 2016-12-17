{
    "i2c": {
        "device": "/dev/i2c-1"
    },
    "serial": {
        "device": "/dev/ttyACM0"
    },
    "network": {
        "ipaddr": "172.16.10.20"
    },
    "sensor" : {
        "IMU": {
            "host": "ARDUINO",
            "type": "BNO055",
            "proto": "I2C",
            "address": "55"
        },
        "DEPTH": {
            "host": "ARDUINO",
            "type": "MS5837",
            "proto": "I2C",
            "address": "0x76"
        },
        "CURRENT": {
            "host": "ARDUINO",
            "type": "ATTOPILOT_A180",
            "proto": "ANALOG",
            "pin": "A0"
        },
        "AMP": {
            "host": "ARDUINO",
            "type": "ATTOPILOT_A180",
            "proto": "ANALOG",
            "pin": "A1"
        }
    },
    "camera": {
        "command": "/usr/local/bin/mjpg_streamer",
        "output": "output_http.so -w /root/mjpg-streamer/mjpg-streamer-experimental/www",
        "input": "input_raspicam.so -x 1366 -y 768",
        "kill": "kill -9 `pidof mjpg_streamer`",
        "tilt": {
            "x": {
                "host": "ARDUINO",
                "proto": "PWM",
                "pin": 10,
                "neutral": 1500,
                "min": 1100,
                "max": 1900,
                "reverse": 0 
            },
            "y": {
                "proto": "NONE"
            }
        }
    },
    "motor": {
        "1": {
            "host": "ARDUINO",
            "proto": "PWM",
            "pin": 3,
            "neutral": 1500,
            "min": 1100,
            "max": 1900,
            "direction": 48,
            "reverse": 0 
        },
        "2": {
            "host": "ARDUINO",
            "proto": "PWM",
            "pin": 4,
            "neutral": 1500,
            "min": 1100,
            "max": 1900,
            "direction": 15,
            "reverse": 0 
        },
        "3": {
            "host": "ARDUINO",
            "proto": "PWM",
            "pin": 23,
            "neutral": 1500,
            "min": 1100,
            "max": 1900,
            "direction": 48,
            "reverse": 0 
        },
        "4": {
            "host": "ARDUINO",
            "proto": "PWM",
            "pin": 22,
            "neutral": 1500,
            "min": 1100,
            "max": 1900,
            "direction": 15,
            "reverse": 0 
        }
    },
    "light": {
        "1": {
            "host": "ARDUINO",
            "proto": "PWM",
            "pin": 6,
            "off": 1100,
            "on": 1900
        },
        "2": {
            "host": "ARDUINO",
            "proto": "PWM",
            "pin": 20,
            "off": 1100,
            "on": 1900
        }
    }
}
