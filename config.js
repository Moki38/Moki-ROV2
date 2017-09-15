{
    "site": {
        "name": "Groningen,NL"
    },
    "i2c": {
        "device": "/dev/i2c-1"
    },
    "serial": {
        "device": "/dev/ttyACM0"
    },
    "network": {
        "ipaddr": "172.16.10.20"
    },
    "datalogger": {
        "logfile": false,
        "logfile_name": "./log/log-mokirov2.log",
        "maxsize": 5242880,
        "maxfiles": 5,
        "logstash": false,
        "host": "82.72.116.14",
        "port": 1520,
        "nodename": "MokiROV2"
    },
    "camera": {
        "config": "0",
        "command": "/usr/local/bin/mjpg_streamer",
        "output": "output_http.so -w /root/mjpg-streamer/mjpg-streamer-experimental/www",
        "input": "input_raspicam.so -x 1366 -y 768 -vf -hf",
        "kill": "kill -9 `pidof mjpg_streamer`"
    }
}
