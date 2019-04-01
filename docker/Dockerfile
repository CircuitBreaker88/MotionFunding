#FROM debian:stretch
FROM ubuntu:18.04
LABEL maintainer="The Motion Developers <216k155@motioncore.io>"
LABEL description="Dockerised Motion , built from Travis"

RUN apt-get update && apt-get install -y software-properties-common unzip
RUN apt-get install -y wget

RUN wget https://github.com/Motion-Core/motion/releases/download/v5.2.3/motion-qt-linux-18.zip
RUN unzip motion-qt-linux-18.zip
RUN cp motiond /usr/local/bin

VOLUME ["/opt/motion"]

EXPOSE 9888
EXPOSE 9888
EXPOSE 9777
EXPOSE 9777

CMD ["motiond", "--conf=/opt/motion/motion.conf", "--printtoconsole"]