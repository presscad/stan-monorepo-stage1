pipeline {
    agent any
    stages {
        stage('build math') {
            when {
                changeset "**/math/*.*"
            }
            steps {
                echo 'Building math.'
                build job: './math'
            }
        }
        stage('build stan') {
            when {
                changeset "**/stan/*.*"
            }
            steps {
                echo 'Building stan.'
                build job: 'stan'
            }
        }
        stage('build cmdstan') {
            when {
                changeset "**/cmdstan/*.*"
            }
            steps {
                echo 'Building cmdstan.'
                build job: 'cmdstan'
            }
        }
    }
}