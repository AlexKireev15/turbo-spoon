import subprocess
import os
import argparse
import shutil

def processArgs():
    parser = argparse.ArgumentParser()
    parser.add_argument('-c', '--config', dest='config', type=str, help='Add configuration name', default='Release', required=False)
    parser.add_argument('-p', '--platform', dest='platform', type=str, help='Add platform name', default='x64', required=False)
    parser.add_argument('-cl', '--clear', dest='isClear',
                    action='store_true', help='Clear build', default=False, required=False)
    
    return parser.parse_args()

cmdArgs = processArgs()
repPath = os.getcwd().replace('\\', '/')
libOutPath = repPath + "/libs"
libSrcPath = libOutPath + "/_libs_src"

class cmakeBuildObject:
    def __init__(self, outPath, srcPath, buildPath, cmakeSrcPath):
        self.outPath = libOutPath + '/' + outPath + '/' + cmdArgs.platform + '/' + cmdArgs.config
        self.srcPath = libSrcPath + '/' + srcPath
        self.buildPath = self.srcPath + '/' + buildPath
        self.cmakeSrcPath = self.srcPath + '/' + cmakeSrcPath


def execute_impl(cmd):
    popen = subprocess.Popen(cmd, stdout=subprocess.PIPE, universal_newlines=True, shell=True)
    for stdout_line in iter(popen.stdout.readline, ""):
        yield stdout_line 
    popen.stdout.close()
    return_code = popen.wait()
    if return_code:
        raise subprocess.CalledProcessError(return_code, cmd)
        
def execute(cmd):
    for res in execute_impl(cmd) :
        print(res, end='')

def cmakeBuild(cbo):
    execute(['cmake',
    '-G', 'Visual Studio 17 2022',
    '-A', cmdArgs.platform,
    '-S', cbo.cmakeSrcPath,
    '-B', cbo.buildPath,
    '--install-prefix', cbo.outPath,
    '-D', 'BUILD_SHARED_LIBS=OFF'])
    execute(['cmake',
    '--build', cbo.buildPath,
    '--config', cmdArgs.config])
    execute(['cmake',
    '--install', cbo.buildPath,
    '--config', cmdArgs.config])

libs = \
[
    cmakeBuildObject("glew", "glew-2.2.0", "build/vc17/" + cmdArgs.platform, "build/cmake"),
    cmakeBuildObject("glfw", "glfw", "build/vc17/" + cmdArgs.platform, ""),
    cmakeBuildObject("glm", "glm", "build/vc17/" + cmdArgs.platform, ""),
    cmakeBuildObject("assimp", "assimp", "build/vc17/" + cmdArgs.platform, "")
]

if cmdArgs.isClear :
    for l in libs :
        try:
            shutil.rmtree(l.outPath, ignore_errors=False, onerror=None)
        except FileNotFoundError:
            print('"' + l.outPath + '" Already deleted')
        try:
            shutil.rmtree(l.buildPath, ignore_errors=False, onerror=None)
        except FileNotFoundError:
            print('"' + l.buildPath + '" Already deleted')
#else :
    #for l in libs :
        #cmakeBuild(l)

execute(['cmake',
    '-G', 'Visual Studio 17 2022',
    '-S', repPath,
    '-B', repPath + '/vc17'])