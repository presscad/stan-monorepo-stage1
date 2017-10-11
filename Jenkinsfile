def setupCC(failOnError = true) {
    errorStr = failOnError ? "-Werror " : ""
    "echo CC=${env.CXX} ${errorStr}> make/local"
}

def setup(String pr, Boolean failOnError = true) {
    errorStr = failOnError ? "-Werror " : ""
    script = """
        make math-revert
        make clean-all
        git clean -xffd
        ${setupCC(failOnError)}
    """
    if (pr != '')  {
        prNumber = pr.tokenize('-').last()
        script += """ 
            cd lib/stan_math
            git fetch https://github.com/stan-dev/math +refs/pull/${prNumber}/merge:refs/remotes/origin/pr/${prNumber}/merge
            git checkout refs/remotes/origin/pr/${prNumber}/merge
        """
    }
    return script
}

def mailDevs(String label) {
    emailext (
        subject: "[StanJenkins] ${label}: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]'",
        body: """${label}: Job '${env.JOB_NAME} [${env.BUILD_NUMBER}]': Check console output at ${env.BUILD_URL}""",
        recipientProviders: [[$class: 'DevelopersRecipientProvider']]
    )
}

def runTests(String testPath) {
    "runTests.py -j${env.PARALLEL} ${testPath} || echo ${testPath} failed"
}

pipeline {
    agent none
    parameters {
        string(defaultValue: '', name: 'math_pr', description: "Leave blank "
                + "unless testing against a specific math repo pull request.")
    }
    options { skipDefaultCheckout() }
    stages {
        stage('Linting & Doc checks') {
            agent any
            steps {
                script {
                    checkout scm
                    sh setup(params.math_pr)
                    stash 'StanSetup'
                    parallel(
                        CppLint: { sh "make cpplint" },
                        documentation: { sh 'make doxygen' },
                        manual: { sh 'make manual' },
                        headers: { sh "make -j${env.PARALLEL} test-headers" },
                        failFast: true
                    )
                }
            }
            post { always { deleteDir() } }
        }
        stage('Tests') {
            failFast true
            parallel {
                stage('Windows Unit') {
                    agent { label 'windows' }
                    steps {
                        unstash 'StanSetup'
                        bat setupCC(false)
                        bat runTests("src/test/unit")
                        retry(2) { junit 'test/unit/**/*.xml' }
                    }
                    post { always { deleteDir() } }
                }
                stage('Windows Headers') { 
                    agent { label 'windows' }
                    steps {
                        unstash 'StanSetup'
                        bat setupCC()
                        bat "make -j${env.PARALLEL} test-headers"
                    }
                    post { always { deleteDir() } }
                }
                stage('Unit') { 
                    agent any
                    steps {
                        unstash 'StanSetup'
                        sh setupCC(false)
                        sh "./" + runTests("src/test/unit")
                        retry(2) { junit 'test/unit/**/*.xml' }
                    }
                    post { always { deleteDir() } }
                }
                stage('Integration') {
                    agent any
                    steps { 
                        unstash 'StanSetup'
                        sh setupCC()
                        sh "./" + runTests("src/test/integration")
                        retry(2) { junit 'test/integration/*.xml' }
                    }
                    post { always { deleteDir() } }
                }
                stage('Upstream CmdStan tests') {
                    // These will only execute when we're running against the
                    // live PR build, not on other branches
                    when { expression { env.BRANCH_NAME ==~ /PR-\d+/ } }
                    steps {
                        build(job: 'CmdStan/downstream tests',
                              parameters: [string(name: 'stan_pr', value: env.BRANCH_NAME),
                                           string(name: 'math_pr', value: params.math_pr)])
                    }
                }
            }
        }
        stage('Performance') {
            agent { label 'gelman-group-mac' }
            steps {
                unstash 'StanSetup'
                sh setupCC()
                sh """
                    ./runTests.py -j${env.PARALLEL} src/test/performance
                    cd test/performance
                    RScript ../../src/test/performance/plot_performance.R 
                """
            }
            post {
                always {
                    retry(2) {
                        junit 'test/**/*.xml'
                        archiveArtifacts 'test/performance/performance.csv,test/performance/performance.png'
                        perfReport compareBuildPrevious: true, errorFailedThreshold: 0, errorUnstableThreshold: 0, failBuildIfNoResultFile: false, modePerformancePerTestCase: true, sourceDataFiles: 'test/performance/**.xml'
                    }
                    deleteDir()
                }
            }
        }
        stage('Update CmdStan Upstream') {
            agent none
            when { branch "develop" }
            steps {
                sh "curl -O https://raw.githubusercontent.com/stan-dev/ci-scripts/master/jenkins/create-cmdstan-pull-request.sh"
                sh "sh create-cmdstan-pull-request.sh"
            }
        }
    }
    post {
        always {
            node('master') {
                warnings consoleParsers: [[parserName: 'CppLint']], canRunOnFailed: true
                warnings consoleParsers: [[parserName: 'GNU C Compiler 4 (gcc)']], canRunOnFailed: true
                warnings consoleParsers: [[parserName: 'Clang (LLVM based)']], canRunOnFailed: true
            }
        }
        success { mailDevs("SUCCESSFUL") }
        failure { mailDevs("FAILURE") }
    }
}
