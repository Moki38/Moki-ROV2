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
    "camera": {
        "command": "/usr/local/bin/mjpg_streamer",
        "output": "output_http.so -w /root/mjpg-streamer/mjpg-streamer-experimental/www",
        "input": "input_raspicam.so -x 1366 -y 768",
        "kill": "kill -9 pidof mjpg_streamer"
    }
}
