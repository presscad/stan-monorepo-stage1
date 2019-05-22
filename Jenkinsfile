pipeline {
  agent any
  stages {
    stage('Header Check') {
      steps {
        sh '''cd math
make -j${env.PARALLEL} test-headers
cd ..'''
      }
    }
  }
  environment {
    PARALLEL = '1'
  }
}