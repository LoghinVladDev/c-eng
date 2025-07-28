#!/usr/bin/zsh

slangc "$1" -target spirv -profile spirv_1_4 -emit-spirv-directly -fvk-use-entrypoint-name -entry vertexShader -entry fragmentShader -o triangle.spv
