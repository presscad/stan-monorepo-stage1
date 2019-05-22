pipeline {
  agent any
  stages {
    stage('error') {
      parallel {
        stage('error') {
          steps {
            dir(path: 'math')
          }
        }
        stage('') {
          steps {
            dir(path: 'stan')
          }
        }
        stage('') {
          steps {
            dir(path: 'cmdstan')
          }
        }
      }
    }
  }
  environment {
    PARALLEL = '1'
  }
}