pipeline {
  agent any
  stages {
    stage('error') {
      parallel {
        stage('math') {
          steps {
            dir(path: 'math') {
              pwd()
            }

          }
        }
        stage('stan') {
          steps {
            dir(path: 'stan') {
              pwd()
            }

          }
        }
        stage('cmdstan') {
          steps {
            dir(path: 'cmdstan') {
              pwd()
            }

          }
        }
      }
    }
  }
  environment {
    PARALLEL = '1'
  }
}