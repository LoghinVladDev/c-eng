#!/usr/bin/python3

import subprocess
import sys
import os
from pathlib import Path

llvm_cov_path = Path('/Users/vlad.loghin/work/tool/clang-16/bin/llvm-cov')
llvm_profdata_path = Path('/Users/vlad.loghin/work/tool/clang-16/bin/llvm-profdata')


def to_llvm_cov_bins(l: list[str]) -> list[str]:
    if len(l) == 0:
        raise ValueError()

    if len(l) == 1:
        return l

    new_l = [l[0]]
    for e in l[1:]:
        new_l.append('--object')
        new_l.append(e)

    return new_l


if __name__ == '__main__':
    if len(sys.argv) < 3:
        print('Required: path of binaries to merge coverage for and output folder')
        exit(1)

    bin_folder = Path(sys.argv[1])
    out_folder = Path(sys.argv[2])

    for root, _, files in os.walk(bin_folder):
        profraws = []
        bins = []
        for file in files:
            if file.startswith('TestBinary') and not file.endswith('.profraw'):
                binn = f'./{file}'
                bins.append(binn)
                result = subprocess.run([binn], shell=False, cwd=root)
                if result.returncode != 0:
                    print('Test failed')
                    exit(1)
                profraw = f'./{file}.profraw'
                subprocess.run(['mv', './default.profraw', profraw], cwd=root)
                profraws.append(profraw)

        subprocess.run([llvm_profdata_path, 'merge', '-o', 'data.profdata', *profraws], cwd=root)
        subprocess.run([llvm_cov_path, 'show', '--show-branches=count', '--instr-profile', 'data.profdata',
                        *to_llvm_cov_bins(bins)], cwd=root, stdout=open(Path(root) / 'cov.txt', 'w'))

        break
