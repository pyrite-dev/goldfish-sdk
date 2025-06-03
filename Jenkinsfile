pipeline {
	agent any
	environment {
		WEBHOOK_NISHBOX = credentials("webhook-nishbox")
		WEBHOOK_ORIN = credentials("webhook-orin")
		WEBHOOK_PRIVATE1 = credentials("webhook-private1")
	}
	stages {
		stage("Get submodules") {
			steps {
				sh "git submodule update --init --recursive --force"
			}
			post {
				always {
					post_always(true, false)
				}
			}
		}
		stage("Build for Windows") {
			parallel {
				stage("Build for Windows 64-bit") {
					agent any
					steps {
						sh "git submodule update --init --recursive"
						sh "premake5 gmake --engine=dynamic --opengl=gdi"
						sh "gmake config=release_win64 -j9"
						sh "./tool/pack.sh Win64 sdk sdk64.zip"
						archiveArtifacts(
							"sdk64.zip"
						)
					}
					post {
						always {
							post_always(false, false)
						}
					}
				}
				stage("Build for Windows 32-bit") {
					agent any
					steps {
						sh "git submodule update --init --recursive"
						sh "premake5 gmake --engine=dynamic --opengl=gdi"
						sh "gmake config=release_win32 -j9"
						sh "./tool/pack.sh Win32 sdk sdk32.zip"
						archiveArtifacts(
							"sdk32.zip"
						)
					}
					post {
						always {
							post_always(false, false)
						}
					}
				}
			}
			post {
				always {
					post_always(true, true)
				}
			}
		}
	}
}

def post_always(cmt,art){
	def list = [env.WEBHOOK_NISHBOX, env.WEBHOOK_ORIN, env.WEBHOOK_PRIVATE1]
	for(int i = 0; i < list.size(); i++){
		discordSend(
			webhookURL: list[i],
			link: env.BUILD_URL,
			result: currentBuild.currentResult,
			title: "${env.JOB_NAME} - ${env.STAGE_NAME}",
			showChangeset: cmt,
			enableArtifactsList: art,
			description: "**Build:** ${env.BUILD_NUMBER}\n**Status:** ${currentBuild.currentResult}"
		)
	}
}
