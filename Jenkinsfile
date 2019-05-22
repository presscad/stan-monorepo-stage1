pipeline {
  agent any
  stages {
    stage('Header Check') {
      steps {
        sh '''pushd math
make -j${env.PARALLEL} test-headers
popd'''
      }
    }
  }
  environment {
    PARALLEL = '1'
  }
}