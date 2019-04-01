Quick Docker image for motiond
---------------------------

Build docker image:
   
    docker/build.sh

Push docker image:

    docker/push.sh

Pull motioncore/motion:latest from docker hub  at [motion-dockerhub](https://hub.docker.com/r/motioncore/motion/)

    sudo docker pull motioncore/motion
    
Run docker image

    sudo docker run motioncore/motion

Build docker for motiond
----------
A Docker configuration with motiond node by default.

    sudo apt install apt-transport-https ca-certificates curl software-properties-common; curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -; sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"; sudo apt-get update; sudo apt install docker-ce   
---------------------------------------------------        
    
    mkdir motion-mounted-data
    docker run --name motion -d \
     --env 'MOTION_RPCUSER=rpciser' \
     --env 'MOTION_RPCPASSWORD=rpcpassword' \
     --env 'MOTION_TXINDEX=1' \
     --volume ~/motion-mounted-data:~/.motion \
     -p 9888:9888 \
     --publish 9888:9888 \
     motioncore/motion
----------------------------------------------------
Logs

    docker logs -f motion

----------------------------------------------------

## Configuration

Set your `motion.conf` file can be placed in the `motion-mounted data` dir.
Otherwise, a default `motion.conf` file will be automatically generated based
on environment variables passed to the container:

| name | default |
| ---- | ------- |
| BTC_RPCUSER | rpcuser |
| BTC_RPCPASSWORD | rpcpassword |
| BTC_RPCPORT | 9888 |
| BTC_RPCALLOWIP | ::/0 |
| BTC_RPCCLIENTTIMEOUT | 30 |
| BTC_DISABLEWALLET | 1 |
| BTC_TXINDEX | 0 |
| BTC_TESTNET | 0 |
| BTC_DBCACHE | 0 |
| BTC_ZMQPUBHASHTX | tcp://0.0.0.0:28333 |
| BTC_ZMQPUBHASHBLOCK | tcp://0.0.0.0:28333 |
| BTC_ZMQPUBRAWTX | tcp://0.0.0.0:28333 |
| BTC_ZMQPUBRAWBLOCK | tcp://0.0.0.0:28333 |


## Daemonizing

If you're daemonizing is to use Docker's 
[Daemonizing](https://docs.docker.com/config/containers/start-containers-automatically/#use-a-restart-policy),
but if you're insistent on using systemd, you could do something like

```
$ cat /etc/systemd/system/motiond.service

# motiond.service #######################################################################
[Unit]
Description=Motion
After=docker.service
Requires=docker.service

[Service]
ExecStartPre=-/usr/bin/docker kill motion
ExecStartPre=-/usr/bin/docker rm motion
ExecStartPre=/usr/bin/docker pull motioncore/motion
ExecStart=/usr/bin/docker run \
    --name motion \
    -p 9888:9888 \
    -p 9888:9888 \
    -v /data/motiond:/root/.motion \
    motioncore/motion
ExecStop=/usr/bin/docker stop motion
```
