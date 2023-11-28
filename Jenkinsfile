#!/usr/bin/env groovy
pipeline {
    parameters {
        booleanParam(name: 'DEPLOY_BOOL', defaultValue: false, description: 'Deploy to production')
        string(name: 'APP_VERSION', defaultValue: '0.0.0', description: 'Version of the app to be deploy')
        string(name: 'APP_PORT', defaultValue: '8000', description: 'Port of the app to be deploy')
    }
    agent none
    environment {
        APP_NAME = 'frenoi-country-cpp'
    }
    stages {
        stage('BUILD DOCKER') {
            agent any
            options {
                timeout(time: 1, unit: 'HOURS')
            }
            steps {
                sh "docker build -t ${APP_NAME}:${APP_VERSION} --no-cache ."
            }
        }
        stage('DEPLOY') {
            agent {
                label 'pie-node'
            }
            when {
                expression {
                    params.DEPLOY_BOOL
                }
            }
            options {
                timeout(time: 1, unit: 'HOURS')
            }
            steps {
                sh "docker network rm ${APP_NAME} || true"
                sh "docker rmi -f frenoi/${APP_NAME}:${APP_VERSION} || true"
                sh "docker rmi -f localhost:5000/frenoi/${APP_NAME}:${APP_VERSION} || true"
                sh "docker rm -f ${APP_NAME} || true"
                sh "docker network create -d bridge ${APP_NAME}"
                sh "docker build -t frenoi/${APP_NAME}:${APP_VERSION} --no-cache ."
                sh "docker run -p ${APP_PORT}:8000 -d --net=${APP_NAME} --name ${APP_NAME} frenoi/${APP_NAME}:${APP_VERSION}"
                sh "docker update --restart always ${APP_NAME}"
                sh "docker tag frenoi/${APP_NAME}:${APP_VERSION} localhost:5000/frenoi/${APP_NAME}:${APP_VERSION} || true"
                sh "docker push localhost:5000/frenoi/${APP_NAME}:${APP_VERSION} || true"
            }
        }
    }
}
