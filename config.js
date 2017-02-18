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
            "pin": "0"
        },
        "AMP": {
            "host": "ARDUINO",
            "type": "ATTOPILOT_A180",
            "proto": "ANALOG",
            "pin": "1"
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
                "pin": 5,
                "neutral": 1600,
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
            "proto": 1,
	    "pole": 6,
            "pin": 9,
	    "address": 9,
            "neutral": 1500,
            "min": 1100,
            "max": 1900,
            "direction": 0,
            "reverse": 138 
        },
        "2": {
            "host": "ARDUINO",
            "proto": 1,
	    "pole": 6,
            "pin": 10,
	    "address": 10,
            "neutral": 1500,
            "min": 1100,
            "max": 1900,
            "direction": 207,
            "reverse": 138 
        },
        "3": {
            "host": "ARDUINO",
            "proto": 1,
            "pin": 20,
	    "pole": 6,
	    "address": 20,
            "neutral": 1500,
            "min": 1100,
            "max": 1900,
            "direction": 0,
            "reverse": 0 
        },
        "4": {
            "host": "ARDUINO",
            "proto": 1,
            "pin": 21,
	    "pole": 6,
	    "address": 21,
            "neutral": 1500,
            "min": 1100,
            "max": 1900,
            "direction": 0,
            "reverse": 0 
        },
        "5": {
            "host": "ARDUINO",
            "proto": 1,
            "pin": 22,
	    "pole": 6,
	    "address": 22,
            "neutral": 1500,
            "min": 1100,
            "max": 1900,
            "direction": 816,
            "reverse": 0 
        },
        "6": {
            "host": "ARDUINO",
            "proto": 1,
            "pin": 23,
	    "pole": 6,
	    "address": 23,
            "neutral": 1500,
            "min": 1100,
            "max": 1900,
            "direction": 0,
            "reverse": 0 
        }
    },
    "light": {
        "1": {
            "host": "ARDUINO",
            "proto": 1,
            "pin": 3,
            "off": 1100,
            "on": 1900
        },
        "2": {
            "host": "ARDUINO",
            "proto": 1,
            "pin": 4,
            "off": 1100,
            "on": 1900
        }
    }
}
