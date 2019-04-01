#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

DOCKER_IMAGE=${DOCKER_IMAGE:-motioncore/motion}
DOCKER_TAG=${DOCKER_TAG:-latest}

BUILD_DIR=${BUILD_DIR:-.}

rm docker/bin/*
mkdir docker/bin
cp $BUILD_DIR/src/motiond docker/bin/
cp $BUILD_DIR/src/motion-cli docker/bin/
cp $BUILD_DIR/src/motion-tx docker/bin/
strip docker/bin/motiond
strip docker/bin/motion-cli
strip docker/bin/motion-tx

docker build --pull -t $DOCKER_IMAGE:$DOCKER_TAG -f docker/Dockerfile docker
