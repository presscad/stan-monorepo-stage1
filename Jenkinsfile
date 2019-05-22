pipeline {
  agent any
  stages {
    stage('Header Check') {
      parallel {
        stage('Header Check') {
          steps {
            sh '''cd math
make -j${env.PARALLEL} test-headers
cd ..'''
          }
        }
        stage('Clang format') {
          steps {
            sh '''#!/bin/bash
set -x
git checkout -b ${branchName()}
clang-format --version
find stan test -name \'*.hpp\' -o -name \'*.cpp\' | xargs -n20 -P${env.PARALLEL} clang-format -i
if [[ `git diff` != "" ]]; then
  git config --global user.email "mc.stanislaw@gmail.com"
  git config --global user.name "Stan Jenkins"
  git add stan test
  git commit -m "[Jenkins] auto-formatting by `clang-format --version`"
  git push https://${GIT_USERNAME}:${GIT_PASSWORD}@github.com/${fork()}/math.git ${branchName()}
  echo "Exiting build because clang-format found changes."
  echo "Those changes are now found on stan-dev/math under branch ${branchName()}"
  echo "Please \'git pull\' before continuing to develop."
  exit 1
fi'''
          }
        }
      }
    }
  }
  environment {
    PARALLEL = '1'
  }
}