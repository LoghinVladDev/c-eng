#!/usr/bin/zsh

COMPILER_PATH_CLANG="/home/loghin/work/clang/bin"

BW_BUILD_DIR="cmake-build-sonar"
BW_OUT_DIR="$BW_BUILD_DIR/output"
BW="build-wrapper-linux-x86-64"
SSCAN="sonar-scanner"
BW_CLANG_C="$COMPILER_PATH_CLANG/clang"
BW_CLANG_CXX="$COMPILER_PATH_CLANG/clang++"
BW_GCC_C="/usr/bin/gcc"
BW_GCC_CXX="/usr/bin/g++"
BW_C="$BW_GCC_C"
BW_CXX="$BW_GCC_CXX"
BW_CMAKE_GEN="Unix Makefiles"
BW_CMAKE="cmake"
BW_BUILD_THREAD_COUNT=14
BW_PROJ_DIR=$(pwd)
BW_COV_DIR="$BW_BUILD_DIR/coverage"
BW_CTEST="ctest"
BW_GCOV="gcov"
BW_GCOVR="gcovr"
BW_LLVM_COV="$COMPILER_PATH_CLANG/llvm-cov"
BW_LLVM_PROFDATA="$COMPILER_PATH_CLANG/llvm-profdata"
SSCAN_TOKEN="<enter_sq_token_here>"

if [ -d "$BW_BUILD_DIR" ]; then
  rm -rf "$BW_BUILD_DIR"
fi

mkdir "$BW_BUILD_DIR"
mkdir "$BW_OUT_DIR"
mkdir "$BW_COV_DIR"

BW_GCOV_FLAGS="-g -O0 --coverage"
BW_LLVM_COV_FLAGS="-g -O0 -fcoverage-mapping -fprofile-instr-generate"
BW_COV_FLAGS="$BW_GCOV_FLAGS"

"$BW_CMAKE" \
  -S . \
  -B "$BW_BUILD_DIR" \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_C_COMPILER="$BW_C" \
  -DCMAKE_CXX_COMPILER="$BW_CXX" \
  -DCMAKE_CXX_FLAGS="$BW_COV_FLAGS" \
  -DCMAKE_C_FLAGS="$BW_COV_FLAGS" \
  -G "$BW_CMAKE_GEN"

if ! "$BW" --out-dir "$BW_OUT_DIR" cmake --build "$BW_BUILD_DIR/" --target all -- -j "$BW_BUILD_THREAD_COUNT"; then
  echo 'Build failed, cannot continue'
  exit
fi

cd "$BW_BUILD_DIR" || exit

if "$BW_CTEST" --extra-verbose -j "$BW_BUILD_THREAD_COUNT"; then
  echo 'Tests successful'
else
  echo 'Test failed. Check CTest output'
  exit
fi

#exit

#BIN_STR=""
#for f in TestBinary.*; do
#  if ./"$f"; then
#    if [ -z $BIN_STR ]; then
#      BIN_STR="$f"
#    else
#      BIN_STR="$BIN_STR -object $f"
#    fi
#    mv default.profraw ./coverage/"$f".profraw
#  fi
#done

#$BW_LLVM_PROFDATA merge -o ./coverage/merged.profdata ./coverage/*.profraw
#$BW_LLVM_COV show --show-branches=count --instr-profile ./coverage/merged.profdata TestBinary.LoggerDisabled.Naming -object TestBinary.LoggerDisabled -object TestBinary.LoggerEnabled.Naming -object TestBinary.LoggerEnabled > ./coverage/coverage.txt

#cd ./coverage || exit
#$BW_GCOV -b -l -p -c ../**/*.gcno
#$BW_GCOVR -r ..
#cd .. || exit

cd ./coverage || exit
find .. -name '*.o' | xargs gcov --preserve-paths
cd .. || exit

cd "$BW_PROJ_DIR" || exit

"$SSCAN" \
  -Dsonar.projectKey=c-eng \
  -Dsonar.sources=src/engine_v6 \
  -Dsonar.cfamily.build-wrapper-output="$BW_OUT_DIR" \
  -Dsonar.host.url=http://localhost:9000 \
  -Dsonar.token="$SSCAN_TOKEN" \
  -Dsonar.cfamily.gcov.reportsPath="$BW_COV_DIR" \
  -Dsonar.projectVersion=0.0.3.291 \
  -Dsonar.projectName="C Engine"

if [ -d "$BW_BUILD_DIR" ]; then
  rm -rf "$BW_BUILD_DIR"
fi
