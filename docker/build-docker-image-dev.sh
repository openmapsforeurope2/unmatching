#!/bin/sh
PROJECT_NAME=unmatching
DOCKER_TAG="latest"

docker build --no-cache -t $PROJECT_NAME:$DOCKER_TAG -f Dockerfile.dev ./..